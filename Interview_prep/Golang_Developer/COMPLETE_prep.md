# Siemens Go L1 — Complete Prep
Everything in one file. All code compiled and verified on Go 1.22; the outputs shown are real.

**How to use.** Part A is spoken answers, 30 to 60 seconds each — say them out loud, don't read them silently. Part B is output puzzles: cover the answer, predict, then check. Part C is code to write yourself first, then compare.

---

# PART A — TIER 1
*Near certain. Do all of these.*

**1. What is a goroutine? Why is it cheaper than a thread?**
A goroutine is a function running independently, managed by Go itself instead of the operating system. It starts with about 2KB of stack that grows as needed, while an OS thread takes a fixed 1MB or more. Go also switches between goroutines in user space, so there is no kernel call. That is why running a hundred thousand goroutines is normal.

**2. Concurrency vs parallelism?**
Concurrency is many things being in progress at once. Parallelism is many things actually running at the same instant. Concurrency is how you design the program, parallelism depends on how many CPUs you have. In my ping service I check 25,000 devices concurrently, but my pod has 2 CPUs, so only 2 are truly running at any moment. That is fine because the work is waiting on the network, not on CPU.

**3. Buffered vs unbuffered channel?**
Unbuffered means the sender waits until a receiver is ready. Both sides meet at that point, so it acts as a synchronisation point. Buffered means the sender can keep going until the buffer is full. I use buffered channels with a fixed size to absorb bursts, and the fixed size gives me backpressure when things fall behind.

**4. What happens with a closed channel?**
Receiving from a closed channel gives you any buffered values first, then returns the zero value immediately with ok as false. Sending to a closed channel panics. Closing it twice also panics. That is how `for range ch` knows when to stop.

**5. Who should close a channel?**
The sender, always. The receiver has no way to know whether more values are coming, and closing from the receiver side risks a panic if a sender writes after. With multiple senders, I use a WaitGroup and close once they are all done.

**6. How does select work?**
It waits on several channel operations and continues with whichever is ready first. If more than one is ready it picks randomly, so no channel gets starved. Adding a default makes it non-blocking. I use it mostly to combine real work with cancellation, so a long loop can exit when the context is done.

**7. How do slices work internally?**
A slice is three things: a pointer to an array, a length, and a capacity. When you append and there is spare capacity, it writes into the same array. When capacity runs out, Go allocates a bigger array and copies everything over. After that the old and new slices no longer share memory, which is why you must always assign the result of append back.

**8. Array vs slice?**
An array has a fixed length that is part of its type, so `[3]int` and `[4]int` are different types, and it gets copied when you assign it. A slice is a flexible view over an array and is not copied, it shares the same underlying data. In practice you almost always use slices.

**9. byte vs rune?**
A byte is one byte of UTF-8. A rune is one full character. Go strings are stored as UTF-8 bytes, so indexing gives you bytes and `len()` returns bytes, not characters. If I need real character counts I convert to `[]rune`, and `range` over a string already gives me runes.

**10. Are maps safe for concurrent use?**
No. Reading at the same time is fine, but reading while writing crashes the program with a runtime error, not just a race warning. I protect it with a mutex, usually an RWMutex since reads are more common. `sync.Map` exists but it only helps in a narrow case, many reads and few writes on different keys.

**11. How does defer work?**
A deferred call runs when the function returns, in reverse order, and it also runs during a panic. The important detail is that arguments are evaluated when you write the defer, not when it runs. And defers inside a loop pile up until the whole function ends, so I wrap the loop body in a function if I need cleanup per iteration.

**12. Mutex vs RWMutex?**
Mutex allows one goroutine at a time. RWMutex allows many readers or one writer. RWMutex is better when reads are much more common, but it has more overhead per operation, so for very short critical sections a plain Mutex can be faster. Neither can be locked twice by the same goroutine, that deadlocks.

**13. What is WaitGroup, and what is the common bug?**
It waits for a group of goroutines to finish. You call Add before starting, Done inside the goroutine, and Wait in the caller. The common bug is calling Add inside the goroutine instead of before it, because then Wait can run before Add and return too early. If I also need errors back, I use errgroup instead.

**14. What is a race condition?**
Two goroutines touching the same memory at the same time, with at least one writing, and no synchronisation between them. The result depends on timing, so it happens intermittently and is hard to reproduce. I prevent it with a mutex, or by not sharing at all and passing data through channels. To detect it I run tests with the `-race` flag, and I run it against integration tests because it only catches races that actually happen during that run.

**15. How do interfaces work?**
An interface is a set of method signatures, and any type with those methods satisfies it automatically. There is no implements keyword. The useful part is that the interface can be defined by the code that uses it, not the code that implements it. So in my services the repository interface only has the methods that service actually needs, which makes it easy to swap in a fake for tests.

**16. How does Go handle errors?**
Errors are ordinary return values, not exceptions. So the error path is visible in the code instead of jumping somewhere invisible. I wrap errors with `fmt.Errorf` and `%w` to add context at each layer, which builds a trail of what was happening. The rule I follow is wrap everywhere, handle once, at the layer that can actually do something about it.

**17. errors.Is vs errors.As?**
`Is` checks whether a specific known error is somewhere in the wrap chain, like `sql.ErrNoRows`. `As` looks for a specific error type and gives it to you so you can read its fields. So Is is for identity, As is for type.

**18. What is context for?**
It carries cancellation and deadlines through a chain of function calls. I pass it as the first parameter, always defer cancel, and check `ctx.Done()` inside long loops. Cancelling a parent cancels everything below it, so when a client disconnects the database query gets cancelled too instead of running for nothing.

**19. Value receiver vs pointer receiver?**
A value receiver gets a copy, so changes do not stick. A pointer receiver works on the original. I use a pointer when I need to change state, when the struct is large enough that copying matters, or when it contains a mutex, because copying a mutex is a bug. I also keep it consistent across one type.

**20. Functions vs methods?**
A function stands alone. A method has a receiver, so it belongs to a type. Methods are what let a type satisfy an interface, since interfaces are defined by methods. And the receiver being a value or pointer decides which interfaces the type satisfies.

---

---

# PART A — TIER 2
*Likely, especially the Go-internals flavour.*

**1. Explain the GMP scheduler.**
G is a goroutine, M is an OS thread, P is a processor context that holds a queue of runnable goroutines. There are GOMAXPROCS of them. A thread needs a P to run Go code. Each P has its own queue and steals work from other Ps when idle, which keeps the load even. If a goroutine blocks on a syscall, the thread detaches so another thread can pick up that P and keep working.

**2. How does Go's garbage collector work?**
It is a concurrent tri-colour mark and sweep collector. Tri-colour means objects are marked white, grey or black as it scans, and whatever is still white at the end is unreachable and gets freed. The key point is that it runs alongside your program, so pauses are under a millisecond. GOGC controls when it triggers, the default means it collects once the heap has doubled.

**3. Stack or heap, how does Go decide?**
The compiler decides using escape analysis. If a value can outlive the function, because you return it, store it globally, capture it in a goroutine, or put it in an interface, it escapes to the heap. Otherwise it stays on the stack, which is much cheaper because it is freed automatically. You can see the decisions with `-gcflags=-m`.

**4. What is GOMAXPROCS, and what breaks in containers?**
It is how many OS threads can run Go code at the same time, and it defaults to the number of CPUs. The container problem is that Go used to see the host's CPU count instead of the container's CPU limit. So a pod limited to one CPU would create dozens of threads and get heavily throttled. Newer Go reads the cgroup limit, and on older versions you set it manually or use the automaxprocs library.

**5. What are method sets?**
The method set of a value type only includes value receiver methods. The method set of a pointer includes both. So a pointer can satisfy more interfaces than the value can. If a method has a pointer receiver, the plain value does not implement that interface, only the pointer does. That is the most common compile error people hit in Go.

**6. Why can a non-nil interface hold a nil pointer?**
Because an interface stores two things, a type and a value. If you return a nil pointer as an error, the type part is still filled in, so the interface itself is not nil. Then `if err != nil` becomes true even though nothing failed. The fix is to return plain nil instead of a typed nil pointer.

**7. What is a goroutine leak?**
A goroutine that is blocked forever, usually waiting on a channel that nobody will write to. It holds its stack and everything it captured, so memory grows steadily and looks like a memory leak. I track `runtime.NumGoroutine()` as a metric and watch for it climbing without coming back down, and pprof shows me where they are stuck. The prevention is simple, every goroutine needs a way to exit, usually a context.

**8. How do you gracefully shut down a service?**
Order matters. Stop accepting new work first, then finish what is already in progress, then cancel the context so background goroutines unwind, then close the database and Kafka connections last. I catch SIGTERM with `signal.NotifyContext`. In Kubernetes I also make sure the grace period is longer than my worst case processing time, otherwise the pod gets killed mid-work.

**9. How do you bound concurrency?**
Two ways. A worker pool, where a fixed number of goroutines all read from one jobs channel. Or a buffered channel used as a semaphore, where you send a token before starting work and receive it when done, so the buffer size is your limit. I size it near the CPU count for CPU heavy work and much higher for work that mostly waits on the network.

**10. How do you implement a timeout correctly?**
With `context.WithTimeout`, passed down so the actual operation can be cancelled. Using `select` with `time.After` only stops you waiting, it does not stop the work underneath, so the goroutine keeps running and you leak it. The real answer is that the operation itself has to be cancellable.

**11. Go has no inheritance, so how do you reuse code?**
Composition, using struct embedding. Embedding a type gives the outer struct its fields and methods, so it looks like inheritance, but it is delegation, there is no overriding. Polymorphism comes from interfaces instead. It is a deliberate choice, deep inheritance trees get rigid and spread behaviour across levels.

**12. How do you get OOP features in Go?**
Encapsulation comes from capitalisation, uppercase is exported and lowercase is private, so the package is the boundary. Abstraction and polymorphism both come from interfaces. Inheritance is deliberately missing and replaced by composition. So three of the four are there, and the fourth is replaced by something simpler.

**13. panic vs log.Fatal vs returning an error?**
Returning an error is the normal path, for anything the caller can handle. Panic is for programmer errors that should never happen, and it can be caught with recover inside a defer, which is how HTTP middleware stops one bad request killing the server. `log.Fatal` calls `os.Exit`, so it skips all deferred functions and cannot be recovered. I only use Fatal in main during startup, never in a handler or a library.

**14. make vs new?**
`new` allocates zeroed memory and returns a pointer. `make` is only for slices, maps and channels, it sets up the internal structure and returns the type itself, not a pointer. In practice you almost always want make.

**15. What is sync.Once for?**
Running something exactly once, safely, even when many goroutines call it. Typically lazy initialisation, like building a client or loading config the first time it is needed. It is the correct way to do a lazy singleton in Go, instead of the double checked locking people write in other languages.

**16. When do you use atomics instead of a mutex?**
For a single value, like a counter or a flag or a pointer you swap. Atomic operations are cheaper because nothing blocks. As soon as I need to update two related fields together and keep them consistent, atomics are not enough and I need a mutex.

---

---

# PART A — TIER 3
*Deeper probes. Lower priority for an L1.*

**1. What is sync.Pool, and when is it misused?**
It keeps a pool of temporary objects you can reuse instead of allocating fresh ones, which cuts garbage collector pressure in hot paths. A typical use is reusing byte buffers. The misuse is treating it as a cache: objects can be dropped at any garbage collection, there is no size limit or TTL, and you have to reset an object when you take it out. So it is for reducing allocations, not for storing anything you need later.

**2. What causes a deadlock in Go?**
Sending on a channel with no receiver, receiving with no sender, a WaitGroup counter that never reaches zero, or two goroutines locking the same two mutexes in opposite order. If every goroutine is blocked, the runtime detects it and panics. The dangerous case is when one goroutine is still alive, because then it just hangs silently with no error.

**3. Why is map iteration order random?**
Go deliberately randomises it so nobody writes code that depends on the order. If it were accidentally stable, people would rely on it and then break when the implementation changed. If I need a specific order I collect the keys, sort them, and iterate over that.

**4. What is a nil channel useful for?**
A nil channel blocks forever on both send and receive. That sounds useless, but in a `select` it means that case can never be chosen. So if one input channel is finished, I set the variable to nil and that case is effectively switched off, while the other cases keep working. It is the clean way to drop an input from a select loop.

**5. What are generics good for, and when do you avoid them?**
Type parameters let you write one implementation that works for many types, so you stop duplicating the same function for int, string and so on. Good uses are small utilities like Map and Filter, a typed cache, or a generic worker pool. I avoid them when a plain interface is clearer, or when I am adding type parameters for a flexibility nobody actually needs.

**6. What is the zero value principle?**
Every type in Go has a usable zero value and variables are always initialised, so there is no undefined memory. A `sync.Mutex` works at zero value, a `bytes.Buffer` is ready to write to, and you can append to a nil slice. Good Go design means making the zero value of your own types usable too, so callers do not need a constructor for the simple case.

**7. How do you structure a production Go service?**
Three layers with interfaces between them. Handlers or transport at the edge, which only do HTTP or gRPC. A service layer with the business logic. A repository layer that owns the database. Dependencies are created in main and passed downward, so nothing constructs its own dependencies. Directory-wise, `cmd/` for entry points and `internal/` for code that should not be imported from outside.

**8. How do you test code with timeouts or TTLs?**
I put time behind an interface, a small Clock with a Now method, and inject it. In production it returns the real time, in tests it returns whatever I want. That means I can test that a cache entry expired or a rate limiter refilled without any `time.Sleep`, so the tests are fast and deterministic instead of flaky.

**9. Fan-out and fan-in?**
Fan-out is several goroutines reading from one channel to process work in parallel. Fan-in is the reverse, merging several channels into one output. For fan-in I start one goroutine per input that forwards into a shared output channel, and a WaitGroup closes the output once every input is drained.

---

---

# PART B — CODE OUTPUT PUZZLES

Cover the answer. Predict the output. Then check.
These are the questions that separate real Go experience from theory.

---

### Puzzle 1 — slice aliasing

```go
s := []int{1, 2, 3, 4, 5}
a := s[:2]
fmt.Println(len(a), cap(a))
a = append(a, 99)
fmt.Println(s)
```

<details>

**Output:**
```
2 5
[1 2 99 4 5]
```

**Why:** `a` has len 2 but cap 5, because slicing keeps the original backing array from the start point. So `append` has room and writes *in place* — overwriting `s[2]`. If cap had been exhausted, Go would have allocated a new array and `s` would be untouched.

**The lesson:** whether append mutates the original depends on capacity, which is why this bug feels random.
</details>

---

### Puzzle 2 — nil pointer in an interface ⭐

```go
type MyErr struct{}
func (e *MyErr) Error() string { return "boom" }

func mightFail() error {
    var p *MyErr = nil
    return p
}

err := mightFail()
fmt.Println(err == nil)
```

<details>

**Output:**
```
false
```

**Why:** an interface holds (type, value). Here the type is `*MyErr` and the value is nil. Since the type slot is filled, the interface itself isn't nil. So `if err != nil` fires even though nothing went wrong.

**The fix:** return a literal `nil`, never a typed nil pointer.
</details>

---

### Puzzle 3 — defer argument evaluation

```go
i := 0
defer fmt.Println("deferred i =", i)
i = 100
fmt.Println("final i =", i)
```

<details>

**Output:**
```
final i = 100
deferred i = 0
```

**Why:** arguments are evaluated when the `defer` statement runs, not when the deferred call executes. `i` was 0 at that moment.

**Follow-up they may ask:** how would you make it print 100? Wrap it in a closure — `defer func() { fmt.Println(i) }()` — because the closure reads `i` at call time.
</details>

---

### Puzzle 4 — defer modifying a named return

```go
func f() (result int) {
    defer func() { result *= 2 }()
    return 5
}
fmt.Println(f())
```

<details>

**Output:**
```
10
```

**Why:** `return 5` assigns 5 to the named return variable, *then* deferred functions run, *then* the function actually returns. So the defer can modify the result. This only works with a named return value.

**Where it's used in real code:** error wrapping in a defer, or recovering from a panic and converting it to an error.
</details>

---

### Puzzle 5 — string length

```go
s := "héllo"
fmt.Println(len(s))
fmt.Println(len([]rune(s)))
for i := range s { fmt.Print(i, " ") }
```

<details>

**Output:**
```
6
5
0 1 3 4 5
```

**Why:** `é` takes 2 bytes in UTF-8, so `len(s)` is 6 bytes for 5 characters. `range` yields *byte offsets* of each rune, which is why index 2 is skipped — that's the second byte of `é`.

**The lesson:** `len()` is bytes. Convert to `[]rune` for character counts.
</details>

---

### Puzzle 6 — nil map

```go
var m map[string]int
fmt.Println(m["x"], len(m))
m["x"] = 1
```

<details>

**Output:**
```
0 0
panic: assignment to entry in nil map
```

**Why:** reading from a nil map is safe and returns the zero value. **Writing panics.** A nil map is readable but not writable — you must `make` it first.

**Common trap:** a struct with a map field that was never initialised.
</details>

---

### Puzzle 7 — receiving from a closed channel

```go
ch := make(chan int, 2)
ch <- 1
close(ch)
v1, ok1 := <-ch
v2, ok2 := <-ch
fmt.Println(v1, ok1, "|", v2, ok2)
```

<details>

**Output:**
```
1 true | 0 false
```

**Why:** closing doesn't discard buffered values — you drain them first, with `ok == true`. Once empty, receives return the zero value immediately with `ok == false`. That's how `for range ch` knows to stop.
</details>

---

### Puzzle 8 — two slices sharing an array

```go
s := make([]int, 0, 5)
s = append(s, 1, 2, 3)
t := s[:2]
t = append(t, 77)
fmt.Println(s, t)
```

<details>

**Output:**
```
[1 2 77] [1 2 77]
```

**Why:** `t` shares `s`'s backing array with spare capacity, so appending to `t` overwrites `s[2]`. Both slices see the change.

**The fix if you want independence:** `t := append([]int(nil), s[:2]...)` or use a full slice expression `s[:2:2]` to cap the capacity, forcing the next append to allocate.
</details>

---

### Puzzle 9 — loop variable capture ⭐ (version-dependent)

```go
for i := 0; i < 3; i++ {
    go func() { fmt.Println(i) }()
}
```

<details>

**Go 1.22 and later:** prints 0, 1, 2 in some order. Each iteration gets its own `i`.

**Go 1.21 and earlier:** typically prints `3 3 3` — all goroutines shared one variable.

**Why it matters:** this was the single most common Go bug for a decade, and Go 1.22 changed the semantics. If asked, say both: *"Since 1.22 the loop variable is per-iteration, so this is fine now. Before 1.22 you had to pass it as a parameter or shadow it with `i := i`."* Knowing the change is a strong signal.
</details>

---

### Puzzle 10 — method sets ⭐

```go
type Speaker interface{ Speak() string }
type Dog struct{}
func (d *Dog) Speak() string { return "woof" }

var s Speaker = Dog{}
```

<details>

**Output:** compile error.

```
cannot use Dog{} (value of type Dog) as Speaker value:
Dog does not implement Speaker (method Speak has pointer receiver)
```

**Why:** `Speak` has a pointer receiver, so only `*Dog` has it in its method set. `Dog` doesn't implement the interface.

**The fix:** `var s Speaker = &Dog{}`.

**Reverse case:** if the receiver were a value receiver, both `Dog` and `*Dog` would satisfy it.
</details>

---

### Puzzle 11 — arrays are values

```go
a := [3]int{1, 2, 3}
b := a
b[0] = 99
fmt.Println(a, b)
```

<details>

**Output:**
```
[1 2 3] [99 2 3]
```

**Why:** arrays are copied on assignment because the length is part of the type. Slices are not — they'd share the backing array. This is the cleanest way to show you understand the array/slice distinction.
</details>

---

### Puzzle 12 — nil slice

```go
var s []int
fmt.Println(s == nil, len(s), cap(s))
s = append(s, 1)
fmt.Println(s, s == nil)
```

<details>

**Output:**
```
true 0 0
[1] false
```

**Why:** a nil slice is perfectly usable — `len`, `cap`, `range` and `append` all work on it. Append allocates on first use. That's the zero value principle: you rarely need to initialise a slice before appending.

**Follow-up:** nil slice vs empty slice (`[]int{}`)? Both have len 0 and behave identically in practice, but `s == nil` differs, and they marshal differently in JSON — nil becomes `null`, empty becomes `[]`.
</details>

---

---

# PART C — REFERENCE CODE

Write these yourself first. Use this to check afterwards.

## 1. Worker pool ⭐ most likely coding ask

```go
func workerPool(ctx context.Context, items []int, workers int) []int {
	jobs := make(chan int)
	results := make(chan int)
	var wg sync.WaitGroup

	for i := 0; i < workers; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for j := range jobs {          // exits when jobs is closed
				select {
				case results <- j * j:
				case <-ctx.Done():         // don't block forever on cancel
					return
				}
			}
		}()
	}

	go func() {                            // feed jobs
		defer close(jobs)
		for _, it := range items {
			select {
			case jobs <- it:
			case <-ctx.Done():
				return
			}
		}
	}()

	go func() { wg.Wait(); close(results) } ()   // close results when workers done

	var out []int
	for r := range results {
		out = append(out, r)
	}
	return out
}
```

**Say while writing:** workers exit by ranging a closed channel; the WaitGroup tells us when it's safe to close results; the context means cancel doesn't leave goroutines stuck; worker count is bounded, not one goroutine per item.

## 2. Two goroutines printing alternately

```go
func alternate(n int) []int {
	odd := make(chan struct{}, 1)   // buffered so the final send never blocks
	even := make(chan struct{}, 1)
	var out []int
	var mu sync.Mutex
	var wg sync.WaitGroup
	wg.Add(2)

	go func() {                      // odd numbers
		defer wg.Done()
		for i := 1; i <= n; i += 2 {
			<-odd
			mu.Lock(); out = append(out, i); mu.Unlock()
			even <- struct{}{}
		}
	}()
	go func() {                      // even numbers
		defer wg.Done()
		for i := 2; i <= n; i += 2 {
			<-even
			mu.Lock(); out = append(out, i); mu.Unlock()
			odd <- struct{}{}
		}
	}()

	odd <- struct{}{}                // kick off
	wg.Wait()
	return out
}
```
Output for n=6: `[1 2 3 4 5 6]`

**The trap:** with unbuffered channels the last goroutine sends to a partner that has already finished its loop, so it blocks forever and `wg.Wait()` hangs. Capacity 1 fixes it. If you hit this live, say so out loud — spotting it is the point of the question.

## 3. Semaphore (bounded concurrency)

```go
sem := make(chan struct{}, maxConcurrent)
var wg sync.WaitGroup
for _, item := range items {
	wg.Add(1)
	go func(x Item) {
		defer wg.Done()
		sem <- struct{}{}              // acquire
		defer func() { <-sem }()       // release
		process(x)
	}(item)
}
wg.Wait()
```
Buffer size is the concurrency limit. `struct{}{}` because it takes zero bytes.

## 4. Graceful shutdown

```go
func main() {
	ctx, stop := signal.NotifyContext(context.Background(),
		syscall.SIGINT, syscall.SIGTERM)
	defer stop()

	srv := &http.Server{Addr: ":8080", Handler: router}

	go func() {
		if err := srv.ListenAndServe(); err != nil &&
			!errors.Is(err, http.ErrServerClosed) {
			log.Fatal(err)
		}
	}()

	<-ctx.Done()                       // wait for SIGTERM
	log.Println("shutting down")

	shutdownCtx, cancel := context.WithTimeout(context.Background(), 15*time.Second)
	defer cancel()

	if err := srv.Shutdown(shutdownCtx); err != nil {   // drain in-flight requests
		log.Println("forced shutdown:", err)
	}
	db.Close()                         // resources last
}
```
**Order:** stop accepting → drain → close resources.

## 5. Fan-in

```go
func fanIn(chans ...<-chan int) <-chan int {
	out := make(chan int)
	var wg sync.WaitGroup
	for _, c := range chans {
		wg.Add(1)
		go func(ch <-chan int) {
			defer wg.Done()
			for v := range ch { out <- v }
		}(c)
	}
	go func() { wg.Wait(); close(out) }()
	return out
}
```

## 6. Rate limiter (token bucket) with injectable clock

```go
type Clock interface{ Now() time.Time }
type realClock struct{}
func (realClock) Now() time.Time { return time.Now() }

type TokenBucket struct {
	mu         sync.Mutex
	tokens     float64
	capacity   float64
	refillRate float64   // tokens per second
	last       time.Time
	clock      Clock
}

func NewTokenBucket(capacity, refillRate float64, c Clock) *TokenBucket {
	return &TokenBucket{
		tokens: capacity, capacity: capacity,
		refillRate: refillRate, last: c.Now(), clock: c,
	}
}

func (t *TokenBucket) Allow() bool {
	t.mu.Lock()
	defer t.mu.Unlock()

	now := t.clock.Now()
	t.tokens += now.Sub(t.last).Seconds() * t.refillRate   // lazy refill
	t.last = now
	if t.tokens > t.capacity { t.tokens = t.capacity }

	if t.tokens >= 1 {
		t.tokens--
		return true
	}
	return false
}
```
**The point to say:** the Clock interface is what makes this testable. With a fake clock I can jump time forward and assert refill without any `time.Sleep`.

## 7. Thread-safe cache

```go
type Cache struct {
	mu sync.RWMutex
	m  map[string]int
}
func NewCache() *Cache { return &Cache{m: make(map[string]int)} }

func (c *Cache) Get(k string) (int, bool) {
	c.mu.RLock()
	defer c.mu.RUnlock()
	v, ok := c.m[k]
	return v, ok
}
func (c *Cache) Set(k string, v int) {
	c.mu.Lock()
	defer c.mu.Unlock()
	c.m[k] = v
}
```
RWMutex because reads dominate. Note the map must be made in the constructor — writing to a nil map panics.

## 8. Timeout

```go
ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
defer cancel()

select {
case res := <-doWork(ctx):
	return res, nil
case <-ctx.Done():
	return nil, ctx.Err()      // context deadline exceeded
}
```
The context must be passed *into* the work, or you stop waiting but the work keeps running and leaks.

---

---

# DSA IN GO — verified

```go
// Longest substring without repeating characters  -> "abcabcbb" = 3
func longestUnique(s string) int {
	last := make(map[rune]int)
	best, start := 0, 0
	for i, ch := range s {                    // range gives runes: UTF-8 safe
		if j, seen := last[ch]; seen && j >= start {
			start = j + 1
		}
		last[ch] = i
		if i-start+1 > best { best = i - start + 1 }
	}
	return best
}

// Two sum  -> [2,7,11,15], 9 = [0 1]
func twoSum(nums []int, target int) []int {
	seen := make(map[int]int, len(nums))
	for i, n := range nums {
		if j, ok := seen[target-n]; ok { return []int{j, i} }
		seen[n] = i
	}
	return nil
}

// Valid anagram
func isAnagram(a, b string) bool {
	if len(a) != len(b) { return false }
	cnt := make(map[rune]int)
	for _, c := range a { cnt[c]++ }
	for _, c := range b {
		cnt[c]--
		if cnt[c] < 0 { return false }
	}
	return true
}

// Valid palindrome (alphanumeric, case-insensitive)
func isPalindrome(s string) bool {
	r := []rune{}
	for _, c := range s {
		if c >= 'A' && c <= 'Z' { c += 32 }
		if (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') { r = append(r, c) }
	}
	for i, j := 0, len(r)-1; i < j; i, j = i+1, j-1 {
		if r[i] != r[j] { return false }
	}
	return true
}

// Sort 0s,1s,2s — Dutch national flag, one pass
func sortColors(a []int) {
	low, mid, high := 0, 0, len(a)-1
	for mid <= high {
		switch a[mid] {
		case 0: a[low], a[mid] = a[mid], a[low]; low++; mid++
		case 1: mid++
		default: a[mid], a[high] = a[high], a[mid]; high--
		}
	}
}

// ---- Linked list ----
type Node struct { Val int; Next *Node }

func reverseIter(h *Node) *Node {
	var prev *Node
	for h != nil { h.Next, prev, h = prev, h, h.Next }   // multi-assign, evaluated left to right
	return prev
}

func reverseRec(h *Node) *Node {
	if h == nil || h.Next == nil { return h }
	rest := reverseRec(h.Next)
	h.Next.Next = h
	h.Next = nil
	return rest
}

func hasCycle(h *Node) bool {                // Floyd's tortoise and hare
	slow, fast := h, h
	for fast != nil && fast.Next != nil {
		slow, fast = slow.Next, fast.Next.Next
		if slow == fast { return true }
	}
	return false
}

func middle(h *Node) *Node {
	slow, fast := h, h
	for fast != nil && fast.Next != nil { slow, fast = slow.Next, fast.Next.Next }
	return slow
}

// Number of islands — DFS, sinks visited land
func numIslands(g [][]byte) int {
	if len(g) == 0 { return 0 }
	rows, cols := len(g), len(g[0])
	var dfs func(r, c int)
	dfs = func(r, c int) {
		if r < 0 || r >= rows || c < 0 || c >= cols || g[r][c] != '1' { return }
		g[r][c] = '0'
		dfs(r+1, c); dfs(r-1, c); dfs(r, c+1); dfs(r, c-1)
	}
	count := 0
	for r := 0; r < rows; r++ {
		for c := 0; c < cols; c++ {
			if g[r][c] == '1' { count++; dfs(r, c) }
		}
	}
	return count
}

// Binary tree level order
type TreeNode struct { Val int; Left, Right *TreeNode }

func levelOrder(root *TreeNode) [][]int {
	if root == nil { return nil }
	var out [][]int
	q := []*TreeNode{root}
	for len(q) > 0 {
		var level []int
		var next []*TreeNode
		for _, n := range q {
			level = append(level, n.Val)
			if n.Left != nil { next = append(next, n.Left) }
			if n.Right != nil { next = append(next, n.Right) }
		}
		out = append(out, level)
		q = next
	}
	return out
}
```

**Verified outputs:**
```
longestUnique("abcabcbb") = 3      twoSum([2,7,11,15],9) = [0 1]
isAnagram("listen","silent") = true isPalindrome("A man, a plan...") = true
sortColors([2,0,2,1,1,0]) = [0 0 1 1 2 2]
reverseIter([1,2,3,4]) = [4 3 2 1]  middle([1..5]) = 3
numIslands = 2                      levelOrder = [[1] [2 3]]
```

**Go habits to show while coding:** nil-check before dereferencing any node; use `range` on strings so UTF-8 is handled; slices as queue (`q = next`) rather than importing anything; multi-assignment for pointer swaps; and say out loud when you're doing something for a Go-specific reason.

---

# GO-SPECIFIC CODING NOTES

- Always `if node == nil` before dereferencing in linked-list and tree problems
- `range` over a string gives runes and byte offsets — say this out loud when it's relevant, it shows you know UTF-8
- Slices as stack: `s = append(s, x)` / `s = s[:len(s)-1]`
- Slices as queue: `head := q[0]; q = q[1:]`
- `strings.Builder` for building strings in a loop
- `sort.Slice(s, func(i, j int) bool { ... })` for custom sorting
- Go 1.21+ has builtin `min` and `max`
- **Copy before storing a slice in a results list** (backtracking), or every entry aliases the same array
- Stick to the standard library — `fmt`, `strings`, `sort`, `math`, `sync`, `context`

---

# PART D — YOUR RESUME, SPOKEN
*Say each of these out loud once. This is how the interview opens.*

## Tell me about your project

> I work on the backend platform for a smart metering system. The company deploys electricity meters at customer sites, and those meters need to be monitored and controlled remotely.
>
> The core problem is scale and unreliability. There are tens of thousands of meters, they sit on mobile networks that drop constantly, and they're low-powered devices that respond slowly. So we can't assume a device is reachable, and we can't do anything sequentially.
>
> My platform does three things. First, health monitoring — we ping 25,000+ meters and know which are online. Second, command and control — the operations team sends commands like disconnect, reconnect, or read meter, and we deliver them reliably and confirm they were executed. Third, firmware upgrades over the air, which means pushing megabytes of firmware to devices in chunks over an unreliable link.
>
> The business value is that field visits are expensive. Every operation we can do remotely saves an engineer driving to a site.

*Keep it to this length. Let them ask for detail.*

## Explain the architecture

> It's event-driven microservices in Go, six services in total.
>
> Data comes in from meters over MQTT and TCP. A parsing service decodes the raw device payloads into structured events and publishes them to Kafka. Kafka is our backbone — several services consume the same stream independently.
>
> On the outbound side, a command service takes API requests, reserves the target device so two commands can't fight over it, publishes the command with MQTT QoS-2 delivery, and tracks acknowledgements through SQS. If no ACK arrives within the timeout, we mark the device offline.
>
> Redis holds hot state — device presence, reservations, and firmware chunks cached from S3. Presence works through TTLs: every heartbeat refreshes a key, so if the key expires the device is offline with no background sweeper needed. PostgreSQL holds durable state and time-series readings, partitioned by time.
>
> Everything runs on Kubernetes on AWS. REST APIs sit in front for the operations dashboard.

**Draw it if you can:** Devices → MQTT/TCP → Parsing service → Kafka → consumers → Postgres + Redis + S3. The command path runs the reverse.

## Bullet 1 — The ping service

> We need to know which meters are alive. I built a service that checks 25,000 meters at the same time instead of one by one. It went from taking hours to a few seconds, and each device gets a result in under 3 seconds.

## Bullet 2 — Command execution platform

> The operations team needs to send commands to meters — disconnect, reconnect, read the meter. I built the system that delivers those commands and confirms they actually happened. It handles about 5,000 commands a minute across six services.

## Bullet 3 — OTA firmware upgrade

> Meters run software, and sometimes it needs updating. Sending someone to each meter is too expensive, so we push new firmware over the network. Firmware is megabytes and the network drops constantly, so it has to be sent in small pieces with confirmation at every step.

## Bullet 4 — Async task orchestration in the parsing service

> The parsing service takes raw data from meters and converts it into readings we can store. The challenge is volume — data comes in faster than we can process it, so I made it concurrent, with limits so it never runs out of memory.

## Bullet 5 — REST APIs

> I built the APIs the operations dashboard uses — listing devices, searching, exporting reports, and bulk operations like pinging 25,000 devices from an uploaded CSV file.

## Bullet 6 — Parsing service redesign

> Every meter model sends data in a different format, so we need parsing rules per model. Those rules used to live in database rows, which meant no history and no testing. I moved them into files in Git, so every change gets reviewed and automatically tested before it goes live.

## Banking project — terms decoded

> A banking backend where users have accounts and can transfer money. The interesting part is making sure money is never lost when two transfers happen at the same time.

---

# STUDY ORDER

## Tonight
1. **Part A Tier 1** — 45 min, out loud, 20 questions
2. **Part C worker pool** — 20 min, typed from scratch, compiled and run
3. **Part D — resume spoken** — 20 min, out loud
4. **Part A Tier 2** — 30 min, out loud, 16 questions
5. **Part C DSA** — 20 min, longest substring + two sum, timed

**Stop at 10pm.** Whatever's left, leave it.

*Only if time remains:* Part A Tier 3 (skim), Part C items 2 to 4.

## Tomorrow morning — 30 min, light
1. **Part B puzzles** — reread the outputs, 10 min
2. **Worker pool** — once more from memory, 10 min
3. **Master sheet sections 1 to 3** — six rules, your opener, resume defenses, 10 min *(separate file)*

**No new material after you wake up.**

## Last 30 minutes
Camera, mic, internet, hotspot backup. Resume open, this file open, water, notebook and pen. Phone silent. Join five minutes early.

## Not tomorrow — later rounds
Part A Tier 3 in depth · Part C Tier 2 code (fan-in, rate limiter, cache, timeout) · Docker, Kubernetes, AWS, SOLID breadth · HLD and capacity math · LLD designs · banking project · behavioural questions and compensation.

---

# THREE HABITS THAT MATTER MORE THAN THE CONTENT

**Answer, then stop.** Most of these are 30 to 45 seconds. Let them ask for more.

**Use your own examples.** Concurrency vs parallelism, bounding concurrency, graceful shutdown and goroutine leaks all have real answers from your production work. Those land far better than textbook ones.

**If you don't know, say so quickly.** One sentence, then move on. Fast honest boundaries read as confidence; waffling to fill silence is what actually costs you.
