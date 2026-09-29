# Answers to the Frequently-Asked Question List
Tailored to your Polaris Smart Metering work. Written the way you should say them.

---

# 1. PROJECT-BASED QUESTIONS

## "Explain your project and the problem it solves."

> I work on the backend platform for a smart metering system. The company deploys electricity meters at customer sites, and those meters need to be monitored and controlled remotely.
>
> The core problem is scale and unreliability. There are tens of thousands of meters, they sit on mobile networks that drop constantly, and they're low-powered devices that respond slowly. So we can't assume a device is reachable, and we can't do anything sequentially.
>
> My platform does three things. First, health monitoring — we ping 25,000+ meters and know which are online. Second, command and control — the operations team sends commands like disconnect, reconnect, or read meter, and we deliver them reliably and confirm they were executed. Third, firmware upgrades over the air, which means pushing megabytes of firmware to devices in chunks over an unreliable link.
>
> The business value is that field visits are expensive. Every operation we can do remotely saves an engineer driving to a site.

*Keep it to this length. Let them ask for detail.*

## "Explain the architecture."

> It's event-driven microservices in Go, six services in total.
>
> Data comes in from meters over MQTT and TCP. A parsing service decodes the raw device payloads into structured events and publishes them to Kafka. Kafka is our backbone — several services consume the same stream independently.
>
> On the outbound side, a command service takes API requests, reserves the target device so two commands can't fight over it, publishes the command with MQTT QoS-2 delivery, and tracks acknowledgements through SQS. If no ACK arrives within the timeout, we mark the device offline.
>
> Redis holds hot state — device presence, reservations, and firmware chunks cached from S3. Presence works through TTLs: every heartbeat refreshes a key, so if the key expires the device is offline with no background sweeper needed. PostgreSQL holds durable state and time-series readings, partitioned by time.
>
> Everything runs on Kubernetes on AWS. REST APIs sit in front for the operations dashboard.

**Draw this if you have a whiteboard:** Devices → MQTT/TCP → Parsing service → Kafka → consumers → Postgres + Redis + S3. Command path runs the reverse.

## "Write a simple GET and POST API following your project's architecture."

Three layers with interfaces between them. Say the layering out loud as you write it.

```go
// ---------- domain ----------
type Device struct {
    ID        string    `json:"id"`
    SerialNo  string    `json:"serial_no"`
    Status    string    `json:"status"`
    CreatedAt time.Time `json:"created_at"`
}

var ErrDeviceNotFound = errors.New("device not found")

// ---------- repository (owns SQL) ----------
type DeviceRepository interface {
    GetByID(ctx context.Context, id string) (*Device, error)
    Create(ctx context.Context, d *Device) error
}

type deviceRepo struct{ db *gorm.DB }

func NewDeviceRepo(db *gorm.DB) DeviceRepository { return &deviceRepo{db: db} }

func (r *deviceRepo) GetByID(ctx context.Context, id string) (*Device, error) {
    var d Device
    err := r.db.WithContext(ctx).First(&d, "id = ?", id).Error
    if errors.Is(err, gorm.ErrRecordNotFound) {
        return nil, ErrDeviceNotFound
    }
    if err != nil {
        return nil, fmt.Errorf("get device %s: %w", id, err)
    }
    return &d, nil
}

func (r *deviceRepo) Create(ctx context.Context, d *Device) error {
    if err := r.db.WithContext(ctx).Create(d).Error; err != nil {
        return fmt.Errorf("create device: %w", err)
    }
    return nil
}

// ---------- service (business logic) ----------
type DeviceService struct {
    repo  DeviceRepository
    cache Cache
}

func NewDeviceService(r DeviceRepository, c Cache) *DeviceService {
    return &DeviceService{repo: r, cache: c}
}

func (s *DeviceService) Get(ctx context.Context, id string) (*Device, error) {
    return s.repo.GetByID(ctx, id)
}

func (s *DeviceService) Register(ctx context.Context, serial string) (*Device, error) {
    d := &Device{ID: uuid.NewString(), SerialNo: serial, Status: "pending"}
    if err := s.repo.Create(ctx, d); err != nil {
        return nil, err
    }
    return d, nil
}

// ---------- handler (HTTP only) ----------
type DeviceHandler struct{ svc *DeviceService }

// GET /v1/devices/:id
func (h *DeviceHandler) GetDevice(c *gin.Context) {
    d, err := h.svc.Get(c.Request.Context(), c.Param("id"))
    if errors.Is(err, ErrDeviceNotFound) {
        c.JSON(http.StatusNotFound, gin.H{"code": "not_found", "message": "device not found"})
        return
    }
    if err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"code": "internal", "message": "unexpected error"})
        return
    }
    c.JSON(http.StatusOK, d)
}

// POST /v1/devices
type createDeviceReq struct {
    SerialNo string `json:"serial_no" binding:"required,min=6"`
}

func (h *DeviceHandler) CreateDevice(c *gin.Context) {
    var req createDeviceReq
    if err := c.ShouldBindJSON(&req); err != nil {
        c.JSON(http.StatusBadRequest, gin.H{"code": "validation_failed", "message": err.Error()})
        return
    }
    d, err := h.svc.Register(c.Request.Context(), req.SerialNo)
    if err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"code": "internal", "message": "unexpected error"})
        return
    }
    c.Header("Location", "/v1/devices/"+d.ID)
    c.JSON(http.StatusCreated, d)
}
```

**Points to say while writing this:**
- The handler only does HTTP — parse, validate, map errors to status codes. No business logic.
- A separate request struct, not the database model, so nobody can set fields they shouldn't.
- `c.Request.Context()` is passed down, so if the client disconnects the database query is cancelled too.
- Repository is an interface, so the service is testable with a fake.
- POST returns 201 with a `Location` header; GET returns 404 as a typed error, not a string match.

---

# 2. CONCURRENCY & GOROUTINES

## "What are goroutines? Concurrency vs parallelism?"

> A goroutine is a function running independently, managed by the Go runtime rather than the operating system. It starts with about 2KB of stack that grows as needed, and Go schedules it in user space onto a small pool of OS threads. That's why running a hundred thousand goroutines is normal, while a hundred thousand threads would kill the machine.
>
> Concurrency is structuring your program so many things are *in progress* at once. Parallelism is many things *executing at the same instant*. Concurrency is a design choice, parallelism is a hardware outcome. A concurrent program on a single core is still concurrent — it just interleaves instead of running simultaneously.

## "Real-time scenario explaining concurrency vs parallelism." ⭐

Use your own system — this is the ideal example:

> In my ping service I ping 25,000 meters. That's concurrency — 25,000 operations in flight at once, because each one is mostly waiting on the network, not using CPU. If I did them sequentially it would take hours.
>
> The parallelism is separate and much smaller. My pod has 2 CPUs, so `GOMAXPROCS` is 2 — only 2 goroutines are actually executing Go code at any instant. The other thousands are parked waiting on network replies.
>
> That's the whole distinction. My concurrency is 25,000, my parallelism is 2. And that's fine, because the work is IO-bound. If it were CPU-bound — say decrypting payloads — then concurrency beyond the core count would buy me nothing.

## "Issues faced due to goroutines?" ⭐ (you have real answers)

> Four real ones.
>
> **Unbounded goroutines.** Early on we spawned a goroutine per device. At 25,000 devices that exhausted file descriptors and memory. Two fixes: a shared raw ICMP socket instead of one per goroutine, and a bounded worker pool instead of unlimited spawning. Later I used semaphore-bounded concurrency in the parsing service for the same reason.
>
> **Goroutine leaks.** Goroutines blocked forever on channels nobody would write to. Memory grew steadily and looked like a leak. We found it by exporting `runtime.NumGoroutine()` as a metric and watching it climb monotonically. Fix was giving every goroutine a context so it always has an exit path.
>
> **Race conditions on shared state.** Our device state registry was read and written by many goroutines. We protected it with a lock — a lock-protected registry giving O(1) lookups. We caught the original bug with the race detector.
>
> **Losing work on shutdown.** Pods restarting mid-processing dropped in-flight messages. Fix was ordered graceful shutdown — stop consuming, drain the queues, commit offsets, then exit — plus a Kubernetes grace period longer than worst-case processing.

## "What is a race condition? How do you prevent it?"

> A race condition is two goroutines accessing the same memory at the same time, with at least one of them writing, and no synchronisation between them. The result depends on timing, so it's intermittent and hard to reproduce.
>
> Prevention: protect shared state with a mutex, or avoid sharing at all by passing data through channels so only one goroutine owns it. For a single counter or flag, atomics are cheaper than a mutex. Detection is `go test -race` — it instruments memory access and reports the two conflicting stacks. Important caveat: it only catches races that actually occur during the run, so I run it against integration tests, not just unit tests.

## "Can we limit CPU usage in goroutines?"

> Not per goroutine — Go gives you no way to cap one goroutine's CPU. What you control is the level above it.
>
> `GOMAXPROCS` caps how many OS threads run Go code simultaneously, so that's your parallelism ceiling. A worker pool caps how many goroutines do work at once. In Kubernetes, the CPU limit on the container is enforced by cgroups — going over means throttling, not being killed.
>
> One important detail: if Go sees the host's CPU count instead of the container's limit, it creates far too many threads and gets heavily throttled. Recent Go versions read the cgroup limit; on older versions you set `GOMAXPROCS` explicitly or use the `automaxprocs` library.
>
> For genuinely CPU-heavy work you also need to yield — a tight loop with no function calls or channel operations can hog a thread, though modern Go preempts asynchronously.

---

# 3. MEMORY & PERFORMANCE

## "What is a memory leak? How do you prevent it?"

> In Go it's not classic leaked memory — the garbage collector handles unreferenced objects. A Go leak is memory that's still *referenced* but will never be used again.
>
> The common causes: an unbounded cache or slice that only grows; goroutines blocked forever, because each one holds its stack and everything it captured; timers or tickers never stopped; response bodies never closed; and slicing a huge array down to a small piece, since the small slice keeps the whole backing array alive.
>
> In my system the fix was bounding things. We used two 10,000-element bounded queues between the decode path and the producers, so if consumers slow down the queue applies backpressure instead of growing without limit. Every cache has a TTL and an eviction policy. Every goroutine has a context.
>
> To find one: confirm real growth from the container memory metric, then take two pprof heap profiles and diff them to see which allocation site is growing. Check goroutine count at the same time, because a goroutine leak looks identical from outside.

## "How does Go handle garbage collection?"

> It's a concurrent, tri-colour mark-and-sweep collector. Tri-colour means objects are white (unvisited), grey (reached but not scanned), or black (fully scanned) — at the end, anything still white is unreachable and freed.
>
> The key point is that it runs concurrently with your program, so pauses are sub-millisecond rather than stop-the-world. It's non-generational and non-compacting, which trades some throughput for that low latency.
>
> `GOGC` controls when it triggers — the default of 100 means it collects when the heap has doubled since the last cycle. `GOMEMLIMIT` sets a soft memory ceiling, which matters a lot in Kubernetes: without it, the heap can grow past the container's memory limit and get OOMKilled. With it, the collector works harder as it approaches that boundary. I set it slightly below the container limit.

## "How do you improve performance in Go?" (likely follow-up)

> Measure before changing anything — pprof for CPU and heap, and benchmarks with `-benchmem` for allocation counts.
>
> Then the usual wins: preallocate slices and maps when you know the size, so you avoid repeated reallocation. Use `strings.Builder` instead of concatenation. Pass large structs by pointer. Reuse buffers with `sync.Pool` in genuinely hot paths. Batch database writes instead of one row at a time — that was one of our biggest wins. And reduce allocations generally, because in Go, GC pressure is usually the real cost, not raw computation.

---

# 4. DATA STRUCTURES & EFFICIENCY

## "Array vs slice? How are slices implemented internally?"

> An array has a fixed length that's part of its type — `[3]int` and `[4]int` are different types — and it's copied whenever you assign or pass it. A slice is a flexible view over an array.
>
> Internally a slice is a three-word header: a pointer to a backing array, a length, and a capacity. When you pass a slice to a function, the header is copied but the pointer isn't, so the function sees the same underlying array.
>
> Append is where it gets interesting. If there's spare capacity, it writes into the existing array in place. If capacity is full, Go allocates a bigger array, copies everything over, and returns a slice pointing at the new one. So after a reallocation the old and new slices no longer share memory — which is why append's return value must always be assigned back.
>
> The consequence people get caught by is aliasing. Two slices can point into the same array, so writing through one is visible through the other. And whether that happens depends on capacity, which makes it feel unpredictable.

## "Buffered vs unbuffered channels?"

> An unbuffered channel is a synchronisation point. The sender blocks until a receiver is ready, so both goroutines meet at that moment. That's useful when you want a guarantee that the other side actually received the value.
>
> A buffered channel lets the sender continue until the buffer is full. That decouples producer and consumer, which is what you want to absorb bursts.
>
> In my parsing service I used bounded buffered channels — two 10,000-element queues — deliberately. Bounded, not unbounded, because the buffer size is my backpressure mechanism. If the consumer falls behind, the producer blocks instead of consuming unlimited memory. An unbuffered channel would have coupled them too tightly and lost throughput; an unbounded one would have hidden the problem until we ran out of memory.

## "What is the rune data type and when do you use it?"

> A rune is an alias for `int32` and represents a single Unicode code point — one actual character. A byte is `uint8`, one byte of UTF-8 encoding.
>
> The distinction matters because Go strings are UTF-8 byte sequences. Indexing a string gives you bytes, so `s[0]` on a non-ASCII string gives you a fragment of a character. `len(s)` returns bytes, not characters. But `range` over a string yields runes with their byte offsets.
>
> I use runes whenever I need real character-level work — reversing a string correctly, counting characters, or validating input that might contain non-ASCII. In our parsing work, device payloads are binary so we work in bytes there, but any human-entered field like a customer name or location has to be handled as runes.

---

# 5. GO LANGUAGE FEATURES

## "Difference between functions and methods?"

> A function is standalone: `func Add(a, b int) int`. A method has a receiver, which attaches it to a type: `func (d *Device) Ping() error`.
>
> Methods give you two things functions don't. They let a type satisfy an interface, since interfaces are defined in terms of methods. And they let you namespace behaviour on the type it belongs to, so `device.Ping()` reads naturally.
>
> One Go-specific detail: the receiver can be a value or a pointer, and that choice determines which interfaces the type satisfies. Only `*T` has access to pointer-receiver methods, so `*T` can satisfy more interfaces than `T`.

## "What is an interface and how does it work?"

> An interface is a set of method signatures. Any type that has those methods satisfies it automatically — there's no `implements` keyword. That implicit satisfaction is the important design difference from Java: the interface can be defined by the code that *consumes* it, not the code that implements it.
>
> Internally an interface value is two words: a pointer to type information, and a pointer to the data. Method calls go through the type information, which is how dynamic dispatch works.
>
> The Go convention is small interfaces defined where they're used. In my services the repository interface has just the methods that particular service needs, which means I can swap in a fake for testing without a mocking framework.
>
> One trap worth mentioning: because the interface holds both a type and a value, putting a nil pointer inside it produces a non-nil interface. If you return a typed nil pointer as an `error`, `err != nil` becomes true even though the pointer is nil.

## "Layman's story to explain interfaces and type assertion." ⭐ (asked more than you'd expect)

> Think of a wall power socket. The socket doesn't care what you plug into it — a lamp, a laptop charger, a kettle. It only cares that the plug has the right shape. That shape is the interface: a contract about the *connection*, not about what the device is.
>
> So the socket says "anything with two round pins works here." A lamp has two round pins, so it works. Nobody had to register the lamp as socket-compatible — it just physically fits. That's implicit interface satisfaction in Go.
>
> Now, type assertion. Suppose the socket is smart and wants to behave differently for a kettle — maybe cut power after ten minutes. It has to look past the plug and ask "are you specifically a kettle?" If yes, it gets the kettle and can use kettle-specific features. If no, it just treats it as a generic appliance.
>
> That's type assertion: `kettle, ok := appliance.(Kettle)`. The `ok` tells you whether the guess was right. And if you assert without checking `ok` and you're wrong, the program panics — like forcing a plug into a socket it doesn't fit.

## "Explain select in channels."

> `select` waits on multiple channel operations at once and proceeds with whichever becomes ready first. It's the channel equivalent of a switch statement.
>
> Three behaviours worth knowing. If several cases are ready, it picks one pseudo-randomly — that's deliberate, so no channel gets starved. Adding a `default` case makes it non-blocking: it takes the default immediately if nothing is ready. And with no ready case and no default, it blocks.
>
> The pattern I use most is combining work with cancellation:
> ```go
> for {
>     select {
>     case msg := <-messages:
>         process(msg)
>     case <-ctx.Done():
>         return ctx.Err()
>     }
> }
> ```
> That's how every long-running loop in my services responds to shutdown.
>
> One clever trick: a nil channel blocks forever, so setting a channel variable to nil disables that case in a select. Useful when one input is exhausted but others continue.

## "How does Go handle errors? Panic vs Fatal?"

> Go treats errors as ordinary return values rather than exceptions. A function returns `(result, error)` and the caller checks it. It's verbose, but the error path is visible in the code instead of hidden in an invisible control flow jump.
>
> I wrap errors with `fmt.Errorf("context: %w", err)` to build a trail of what was happening, then check with `errors.Is` for a known sentinel error or `errors.As` to extract a typed error and read its fields. The rule I follow is: wrap at every layer, handle once, at the level that can actually do something about it.
>
> **Panic** is for genuinely unrecoverable programmer errors — not for control flow. It unwinds the stack, runs deferred functions on the way, and can be caught by `recover` inside a defer. That's how HTTP middleware stops one bad request from killing the whole server.
>
> **`log.Fatal`** logs a message and calls `os.Exit(1)`. The critical difference: it does **not** run deferred functions and cannot be recovered. So no cleanup, no flushing, no graceful shutdown. I only use it in `main` during startup — if config is missing or the database is unreachable, there's no point continuing. Never inside a request handler or a library.

## "How does defer work?"

> A deferred call runs when the enclosing function returns, in reverse order of declaration — last deferred, first executed. It also runs during a panic, which is what makes cleanup reliable.
>
> The detail people miss is that arguments are evaluated when the `defer` statement executes, not when the call runs. So `defer fmt.Println(i)` captures the current value of `i`, not whatever it is later.
>
> The other trap is deferring inside a loop. Defers accumulate until the *function* returns, not the iteration — so opening files in a loop with `defer file.Close()` keeps every file open until the end. Fix is to wrap the loop body in a closure or a helper function.
>
> Main uses: closing resources, unlocking mutexes with `defer mu.Unlock()` so an early return can't leave it locked, and `defer cancel()` for contexts.

## "How do you achieve OOP features in Go?"

> Go has three of the four classic OOP features, and replaces the fourth.
>
> **Encapsulation** — through capitalisation. An uppercase identifier is exported from the package, lowercase is private. So the package is the encapsulation boundary rather than the class.
>
> **Abstraction** — through interfaces. The consumer depends on a set of methods, not a concrete type.
>
> **Polymorphism** — also through interfaces. Different types satisfying the same interface can be used interchangeably, resolved at runtime.
>
> **Inheritance — deliberately absent.** Go replaces it with composition through struct embedding. Embedding a type promotes its fields and methods to the outer struct, so it looks like inheritance, but it's delegation — there's no method overriding and no polymorphism through the embedded type.
>
> That's an intentional design decision. Deep inheritance hierarchies become rigid, and behaviour gets scattered across levels. Composition plus small interfaces gives you the reuse without the coupling.

---

# 6. MICROSERVICES, REST API & KAFKA

## "Authentication vs authorization — and ways to implement them?"

> Authentication is *who are you*. Authorization is *what are you allowed to do*. Authentication comes first, and they fail differently: 401 means you haven't proven who you are, 403 means you have, but you're not permitted.
>
> **Authentication approaches:** session cookies with server-side state — easy to revoke but needs a shared store. JWT or PASETO tokens — stateless, scale horizontally, but can't be revoked before expiry, so you use a short-lived access token plus a revocable refresh token. OAuth2 and OIDC when you're delegating to an identity provider. API keys for service-to-service. And mutual TLS, which is what matters in my domain — devices carry client certificates, so the device itself is authenticated cryptographically rather than by a password.
>
> **Authorization approaches:** role-based access control, where a user has roles and roles have permissions — that's what we use, since operations staff and admins see different things. Attribute-based when the decision depends on context, like which region a user manages. And scopes on a token for third-party access.

## "REST API methods and principles?"

> The methods, by their properties: GET is safe and idempotent, no side effects, cacheable. POST is neither safe nor idempotent — it creates something new. PUT is idempotent and replaces the whole resource, so calling it five times leaves the same state. PATCH is a partial update and isn't guaranteed idempotent. DELETE is idempotent — deleting twice leaves it gone, even if the second call returns 404.
>
> The distinction to be precise about: *safe* means no state change; *idempotent* means repeating it gives the same result.
>
> The principles: resources as plural nouns, no verbs in the URL, hierarchy for relationships like `/devices/{id}/commands`, query parameters for filtering and sorting. Stateless — each request carries everything needed, so any pod can serve it. Correct status codes rather than 200 with an error in the body. And consistent error shapes across every endpoint.
>
> The interesting case is actions that aren't CRUD. Pinging a device isn't a noun, so instead of `/devices/{id}/ping` I model it as creating a resource: `POST /devices/{id}/pings`. That keeps it RESTful and gives you something to query the result of.

## "gRPC vs REST?"

> REST is HTTP with JSON. It's universal, human-readable, cacheable by standard infrastructure, and debuggable with curl. The cost is verbose payloads and no schema enforcement — you find out about a mismatch at runtime.
>
> gRPC uses HTTP/2 with Protocol Buffers. Binary and much smaller on the wire, strongly typed with a schema that generates client and server code, so a breaking change fails at compile time. HTTP/2 gives multiplexing over one connection and supports streaming in both directions.
>
> The tradeoffs: gRPC isn't directly callable from a browser without a proxy, isn't human-readable, and needs the toolchain. So my rule is REST for anything a browser or third party touches, gRPC for service-to-service on internal networks where latency and type safety matter. In my banking project I used exactly that split — REST for the public API, gRPC internally.

## "What is a circuit breaker? Open vs closed state?"

> It stops a failing dependency from taking down your service. Without it, a slow dependency means every request waits for a timeout, and all your workers end up blocked on a service that's already dead.
>
> Three states. **Closed** is normal — requests pass through and failures are counted. When failures cross a threshold it trips to **Open**, where requests are rejected immediately without even attempting the call. That's the point: fail fast instead of waiting. After a cooldown it moves to **Half-open** and allows one trial request through. If that succeeds it closes; if it fails it goes back to open.
>
> I used this for fault isolation in the command execution platform. When one downstream path started failing, the breaker kept it from consuming the worker pool that the other five services also needed.
>
> It pairs with two things: a timeout on every call, because a breaker can't trip on requests that never return, and a fallback — serve stale cached data or a degraded response rather than an error.

## "SOLID principles?" (in Go terms)

> **Single Responsibility** — one reason to change. My layering is this: the handler does HTTP only, the service does business logic, the repository owns SQL. A database change doesn't touch the handler.
>
> **Open/Closed** — open to extension, closed to modification. My parsing service is the example. Parser definitions live in version-controlled CSV files, so adding support for a new meter type means adding a definition, not editing the decode logic.
>
> **Liskov Substitution** — any implementation of an interface must be usable wherever that interface is expected, without surprises. In Go this mostly means don't have an implementation panic or ignore the contract that others honour.
>
> **Interface Segregation** — small, focused interfaces. Go pushes you toward this naturally: `io.Reader` is one method. My repository interfaces only expose the methods the consuming service actually needs, rather than one giant Database interface.
>
> **Dependency Inversion** — depend on abstractions, not concretions. My service holds a `DeviceRepository` interface, not a `*gorm.DB`. That's why it's testable — I inject a fake in tests and the real one in `main`.
>
> The Go note worth adding: without inheritance, SOLID here is mostly about interfaces and composition rather than class hierarchies.

## "What is middleware and how is it implemented?"

> Middleware is code that wraps a request handler to do cross-cutting work — logging, authentication, rate limiting, panic recovery — without every handler repeating it.
>
> It's the decorator pattern. A middleware takes a handler and returns a handler, so you chain them and the request passes through each layer in and back out.
>
> ```go
> func AuthMiddleware(next http.Handler) http.Handler {
>     return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
>         token := r.Header.Get("Authorization")
>         claims, err := verify(token)
>         if err != nil {
>             w.WriteHeader(http.StatusUnauthorized)
>             return
>         }
>         ctx := context.WithValue(r.Context(), userKey, claims.UserID)
>         next.ServeHTTP(w, r.WithContext(ctx))
>     })
> }
> ```
>
> In Gin it's `c.Next()` to continue the chain, or `c.Abort()` to stop it.
>
> **Order matters,** and that's the follow-up question. Recovery must be outermost, or a panic in another middleware isn't caught. Logging next, so you log even rejected requests. Then authentication, then rate limiting per user — which has to come after auth, since you need to know who the user is to limit them.

## "How do you load balance and route traffic in microservices?"

> At the edge, an Ingress or an ALB terminates TLS and routes by host and path to the right service.
>
> Inside the cluster, a Kubernetes Service is the load balancer. It's a stable virtual IP in front of a set of pods, and kube-proxy distributes connections across the healthy ones. Healthy is defined by the readiness probe — a pod failing readiness is removed from the endpoint list, which is how rolling deploys avoid sending traffic to pods still starting up.
>
> That's server-side load balancing, and it has a weakness with HTTP/2 and gRPC: those use long-lived connections, so a single connection sticks to one pod and the balancing never happens. The fixes are a headless Service with client-side load balancing, or a service mesh.
>
> Algorithms: round robin by default, least connections when request durations vary a lot, and consistent hashing when you need the same key to reach the same pod — useful for cache locality.
>
> For message-driven paths, Kafka does the routing itself. Partition assignment spreads work across consumers, and the partition key determines which consumer sees which device — that's load balancing with an ordering guarantee attached, which HTTP load balancers can't give you.

## "Explain the process of encryption and decryption."

> Two families.
>
> **Symmetric** — one key for both encryption and decryption, like AES. It's fast, so it's what actually protects bulk data. The problem is key distribution: both sides need the same secret.
>
> **Asymmetric** — a public/private key pair, like RSA or elliptic curve. Anything encrypted with the public key can only be decrypted with the private key. It solves distribution, because the public key can be shared freely, but it's much slower.
>
> So real systems combine them, and TLS is the example. During the handshake the two sides use asymmetric crypto to authenticate and agree on a shared session key, then switch to symmetric encryption for the actual data. You get the key exchange benefit without the performance cost.
>
> Two distinctions worth making unprompted. **Hashing is not encryption** — it's one-way, there's no decryption. Passwords are hashed with bcrypt or Argon2, which are deliberately slow to resist brute force, never encrypted. And **encoding is not encryption** — base64 is just a representation, which is why a Kubernetes Secret being base64 is encoding, not protection.
>
> In my domain this is concrete: devices authenticate over TLS with client certificates, so the device proves its identity cryptographically rather than with a shared password. That's encryption in transit. Encryption at rest is separate — that's disk-level, like RDS or S3 encryption.

---

# 7. DOCKER, KUBERNETES & CLOUD

## "Dockerfile, docker-compose, CI/CD, secrets — what are they and how do you use them?"

> **Dockerfile** — the recipe for an image. For a Go service I use a multi-stage build: a builder stage with the Go toolchain, then a final stage from `distroless` containing only the compiled binary. I copy `go.mod` and `go.sum` first and run `go mod download` before copying source, so a code change doesn't re-download dependencies. `CGO_ENABLED=0` gives a static binary that needs no libc. That takes the image from around 800MB to about 15MB, with a much smaller attack surface since there's no shell.
>
> One detail worth stating: always use the exec form of ENTRYPOINT — the JSON array. Shell form wraps your process in `/bin/sh -c`, so the shell becomes PID 1 and SIGTERM never reaches your application. Graceful shutdown silently stops working.
>
> **docker-compose** — declarative multi-container setup for local development. My service plus Postgres, Redis and Kafka on one network. I use it for integration tests too, so tests run against real dependencies rather than mocks.
>
> **CI/CD** — on push, GitHub Actions runs lint, unit tests, race detector, then integration tests, then builds and pushes the image tagged with the commit SHA, then deploys to staging. In my parser redesign this mattered specifically: parser definitions are validated against stored test data in CI before they can reach staging, which the old database-driven config had no way to do.
>
> **Secrets** — never in the image, because layers are inspectable even if a later layer deletes the file. Injected at runtime as environment variables or mounted files, from a Kubernetes Secret backed by a real secrets manager. In CI they come from the platform's encrypted secret store.

## "Kubernetes principles and architecture?" ⭐

> The core principle is **declarative desired state**. You don't tell Kubernetes to start three pods — you declare that three should exist, and controllers continuously reconcile reality toward that. If a pod dies, the loop notices the gap and creates another. Everything is built on that reconciliation model.
>
> **Control plane components:**
> - **API server** — the front door. Everything goes through it, including internal components. It handles authentication, authorisation and validation.
> - **etcd** — the distributed key-value store holding all cluster state. It's the single source of truth, and it uses Raft consensus, so it needs an odd number of members for quorum.
> - **Scheduler** — watches for pods with no node assigned and picks one, based on resource requests, affinity rules, taints and tolerations.
> - **Controller manager** — runs the reconciliation loops: the deployment controller, replicaset controller, node controller and others.
>
> **On every worker node:**
> - **kubelet** — talks to the API server, starts and stops containers through the container runtime, and reports node and pod health. It also runs the probes.
> - **kube-proxy** — programs the networking rules that make Service virtual IPs work and distributes traffic to pod endpoints.
> - **Container runtime** — containerd usually, which actually runs the containers.
>
> The flow when you deploy: kubectl sends the manifest to the API server, which stores it in etcd. The deployment controller sees a new Deployment and creates a ReplicaSet, which creates Pod objects. The scheduler assigns them to nodes. The kubelet on each node sees pods assigned to it and starts the containers. No component talks to another directly — everything goes through the API server watching etcd.

## "How do you autoscale containers?"

> Three different axes, and they solve different problems.
>
> **HPA — Horizontal Pod Autoscaler.** Adds and removes pods based on a metric. CPU is the default, but it needs resource requests set or there's no baseline to compute a percentage against. It also supports custom and external metrics.
>
> **VPA — Vertical Pod Autoscaler.** Adjusts the requests and limits of existing pods rather than the count. Useful for right-sizing, but it usually requires a pod restart, so it's less common for serving traffic.
>
> **Cluster Autoscaler.** Adds and removes nodes. Necessary because HPA can create pods that stay Pending forever if no node has room.
>
> For my workload the important point is **what to scale on**. Scaling Kafka consumers on CPU is wrong — a consumer that's badly behind might use very little CPU while waiting on the database. The right signal is **consumer lag**, which is what KEDA does: it's an event-driven autoscaler that reads Kafka lag or SQS queue depth and scales accordingly.
>
> Two constraints worth mentioning. Consumers can never usefully exceed the partition count, so that caps your scaling regardless of what the autoscaler wants. And scaling a consumer group triggers a rebalance, so aggressive scaling can cause rebalance churn that makes lag worse — you need stabilisation windows.

## "What security measures secure a container?"

> **The image:** build from `distroless` or `scratch` so there's no shell and no package manager — a compromised process has almost nothing to work with. Pin base image versions rather than using `latest`. Scan images in CI with something like Trivy. Never bake secrets in, since layer history is inspectable.
>
> **The runtime:** run as a non-root user with a specific UID. Mount the root filesystem read-only. Drop all Linux capabilities and add back only what's needed. Set `allowPrivilegeEscalation: false`. Never run privileged containers. Always set resource limits, because an unlimited container can starve everything else on the node.
>
> **The cluster:** RBAC with least privilege, so a service account can only do what its workload needs. Network policies to restrict pod-to-pod traffic — by default any pod can reach any other, which is usually far too open. Separate namespaces per environment or team. Pod Security Standards to enforce these rules rather than trusting every manifest author.
>
> **Secrets:** Kubernetes Secrets are base64-encoded, not encrypted. They need etcd encryption at rest plus RBAC, or better, an external secrets manager with short-lived credentials. On EKS I'd use IRSA so pods get AWS credentials from a service account rather than stored keys.

## "How do you monitor and troubleshoot failing pods?"

> My order of operations:
>
> `kubectl get pods` for the state and restart count. `kubectl describe pod` is the most useful — it shows events and the last termination reason including the exit code. **Exit 137 means OOMKilled**, exit 1 usually means the application exited on an error. `kubectl logs --previous` gets the crashed container's output, which is the part people forget. `kubectl get events --sort-by=.lastTimestamp` for cluster-level context like scheduling failures or image pull problems.
>
> **CrashLoopBackOff** usually comes down to: a missing ConfigMap or Secret, a liveness probe whose initial delay is too short for the app to boot, an unreachable dependency at startup, or running out of memory.
>
> **Pending** means it can't be scheduled — insufficient CPU or memory on any node, an unsatisfiable affinity rule, a taint with no toleration, or a volume claim that won't bind.
>
> For ongoing monitoring rather than firefighting: Prometheus for metrics with Grafana dashboards — we use Grafana. The metrics I care about are the ones that indicate user pain: p99 latency, error rate, consumer lag, and queue depth, rather than raw CPU. Structured logs with a request ID so I can trace one request across services. And alerts on symptoms, not causes.

## "How do you achieve high availability in a Kubernetes cluster?"

> Layer by layer.
>
> **Control plane:** multiple API server replicas behind a load balancer, and an odd number of etcd members — three or five — spread across availability zones so you keep quorum when one zone fails. On EKS the control plane is managed and already multi-AZ.
>
> **Nodes:** node groups across multiple availability zones, so a zone outage doesn't take the cluster.
>
> **Workloads:** more than one replica, obviously, but the important part is **pod anti-affinity** so replicas don't all land on the same node — three replicas on one node gives you no protection when that node dies. **Topology spread constraints** do the same across zones. A **PodDisruptionBudget** so voluntary disruptions like node drains and upgrades can't take down more than you can afford at once.
>
> **Correct probes**, because HA depends on traffic only reaching healthy pods. And graceful shutdown handling, or every deploy drops requests even with plenty of replicas.
>
> **Data layer:** this is where people forget. Stateless pods being HA doesn't help if Postgres is single-AZ. RDS Multi-AZ for failover, Redis with replication, and Kafka with replication factor 3 and `min.insync.replicas=2` spread across zones.
>
> And the honest caveat: true HA means testing it. Draining a node deliberately and confirming nothing breaks is the only way to know.

---

# 8. CODING CHALLENGES

## "Implement goroutines and channels to solve a problem."

Worker pool — the most likely ask, and it's your daily work:

```go
func processURLs(ctx context.Context, urls []string, workers int) []Result {
    jobs := make(chan string)
    results := make(chan Result)

    var wg sync.WaitGroup
    for i := 0; i < workers; i++ {
        wg.Add(1)
        go func() {
            defer wg.Done()
            for url := range jobs {          // exits when jobs is closed
                select {
                case results <- fetch(url):
                case <-ctx.Done():           // don't block forever on cancel
                    return
                }
            }
        }()
    }

    // feed jobs, respecting cancellation
    go func() {
        defer close(jobs)
        for _, u := range urls {
            select {
            case jobs <- u:
            case <-ctx.Done():
                return
            }
        }
    }()

    // close results once all workers are done
    go func() {
        wg.Wait()
        close(results)
    }()

    var out []Result
    for r := range results {
        out = append(out, r)
    }
    return out
}
```

**Say while writing:** workers exit by ranging over a closed channel; the WaitGroup tells us when to close results; the context means a cancel doesn't leave goroutines blocked; and worker count is bounded rather than one goroutine per URL.

## "Solve a problem using interfaces and maps."

A pluggable parser registry — this mirrors your parsing service redesign, so use it:

```go
type Parser interface {
    Parse(raw []byte) (Reading, error)
}

type registry struct {
    mu      sync.RWMutex
    parsers map[string]Parser   // meter model -> parser
}

func NewRegistry() *registry {
    return &registry{parsers: make(map[string]Parser)}
}

func (r *registry) Register(model string, p Parser) {
    r.mu.Lock()
    defer r.mu.Unlock()
    r.parsers[model] = p
}

func (r *registry) Parse(model string, raw []byte) (Reading, error) {
    r.mu.RLock()
    p, ok := r.parsers[model]
    r.mu.RUnlock()
    if !ok {
        return Reading{}, fmt.Errorf("no parser for model %q", model)
    }
    return p.Parse(raw)
}
```

**Say:** adding a new meter type means registering a new implementation, not editing this code — that's Open/Closed. `RWMutex` because reads massively outnumber writes. The comma-ok check because a missing key returns a nil interface, and calling a method on it would panic.

## "Two pointers and sliding window."

**Two pointers** — pair summing to a target in a sorted array:
```go
func twoSum(nums []int, target int) (int, int) {
    l, r := 0, len(nums)-1
    for l < r {
        sum := nums[l] + nums[r]
        switch {
        case sum == target:
            return l, r
        case sum < target:
            l++
        default:
            r--
        }
    }
    return -1, -1
}
```

**Sliding window** — longest substring without repeating characters:
```go
func longestUnique(s string) int {
    last := make(map[rune]int)   // char -> last index seen
    best, start := 0, 0
    for i, ch := range s {       // range gives runes, handles UTF-8
        if j, seen := last[ch]; seen && j >= start {
            start = j + 1        // shrink window past the duplicate
        }
        last[ch] = i
        if i-start+1 > best {
            best = i - start + 1
        }
    }
    return best
}
```

**Note:** `range` over a string gives runes and byte offsets — mention that you're handling UTF-8 correctly rather than assuming ASCII. Small detail, but it signals you actually know Go strings.

---

# QUICK CHECK

Before the interview, make sure you can say these without looking:
- [ ] Project explanation in 60 seconds
- [ ] Architecture, drawn
- [ ] Concurrency vs parallelism using **your ping service** (25,000 concurrent, 2 parallel)
- [ ] Goroutine problems you actually hit
- [ ] The socket-and-plug story for interfaces
- [ ] Panic vs `log.Fatal` (Fatal skips defers, can't be recovered)
- [ ] Circuit breaker three states
- [ ] Kubernetes control plane components
- [ ] Worker pool written from memory
