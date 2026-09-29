# MASTER SHEET (Simple Version) — Siemens Golang Developer
**Thursday 3:00 PM** · Read Part 1, 2 and 3 before the call. Use the rest to look things up.

**How to use this:** Every explanation below is written the way you should say it out loud. Read it, then say it in your own words. If you can say it without looking, you know it.

---

# PART 1 — SIX RULES

**1. Your resume is the interview.**
Every number you wrote will be questioned. For each one know: what it was before, how you measured it, and what went wrong along the way.

**2. Always give the trade-off.**
Don't just name the tool. Say why you picked it and what it cost you.
Weak: "We used Redis."
Strong: "We used Redis because we needed sub-millisecond lookups. The cost is that it's in memory, so we had to handle eviction and keep the real state in Postgres."

**3. Answer in 60–90 seconds, then stop.**
This round covers many topics. Give a complete short answer and let them ask more. Talking too long is the most common mistake.

**4. Never bluff.**
If you don't know something, say so in one line and move on. Saying "I haven't used Flink, but I built windowing by hand in Go" sounds confident. Guessing sounds weak.

**5. Your three weak spots.** Prepare these answers now:
- Docker and Kubernetes — you have less hands-on depth here
- Testing — the job description asks twice, your resume never mentions it
- 2 years experience vs the 3–5 they asked for

**6. Say yes to Pune clearly.**
Give a date. If you sound unsure here, a good technical round can still be wasted.

---

# PART 2 — YOUR OPENING ANSWER

They will start with "tell me about yourself." Say this:

> I'm a backend engineer with two years at Polaris Smart Metering. I work almost fully in Go on IoT systems.
>
> My main work is managing large device fleets. I built a service that pings and controls more than 25,000 smart meters over MQTT and TCP. I also built a command platform across six microservices that handles around 5,000 commands per minute, and a firmware upgrade system that pushes updates to devices over the air.
>
> My stack is Go, Kafka, Redis, PostgreSQL and AWS, running on Kubernetes. Most of my work is concurrency and reliability — worker pools, atomic Redis operations, acknowledgement tracking, offline detection, and circuit breakers.
>
> I'm interested in this role because it's the same kind of problem at a much bigger scale. Siemens builds industrial IoT as a product. I've been solving a smaller version of it, and I'd like to do that inside a bigger engineering team.

Then stop talking. Don't add more.

---

# PART 3 — QUESTIONS ABOUT YOUR RESUME

These are the most likely questions in the whole interview.

**"Tell me about the ping service. How did you get 300x?"**
Earlier the system pinged devices one by one. I changed it to use one shared raw ICMP socket with a pool of goroutines, so thousands of pings go out in parallel. I used one socket instead of one per goroutine because separate sockets would use up file descriptors and duplicate kernel buffers. The 4MB buffer was sized for the burst of replies coming back. The 300x is measured against the old sequential version.

**"What about the 5% that failed?"**
Some devices were genuinely offline. Some had network problems on the meter side. And a small number replied slower than our 3 second limit. *(Never claim 100%. Knowing your failure cases makes you sound experienced.)*

**"Why did you use Lua scripts in Redis?"**
I needed to check if a device was free and reserve it in one single step. If I did it in two separate commands, another request could sneak in between them. Redis runs commands one at a time on a single thread, so a Lua script runs fully without interruption. If the pod dies while holding a reservation, the key has a TTL so it expires and is released automatically.

**"Why one consumer group per pod? You lost Kafka's rebalancing."** ⚠️ *Expect them to push back here.*
That's correct, and it was a deliberate trade. Rebalances were stopping our whole consumer group and causing lag. By giving each pod its own group, no pod affects the others. What I gave up is automatic failover — if a pod dies, its partitions are not picked up by another pod. Today I would first try cooperative rebalancing, which moves only the partitions that need to move instead of stopping everyone.

**"You use Kafka and SQS both. Why?"**
They do different jobs. Kafka is my ordered stream — I can replay it, and multiple services can read the same data independently. SQS is a work queue where each message is one task. It gives me a per-message visibility timeout and an easy dead letter queue, and it has no partition limit. So when Kafka consumers fall behind, SQS absorbs the extra load without me having to add partitions.

**"Explain the OTA firmware upgrade system."**
Firmware is split into chunks of 100 packets. Chunks are cached from S3 into Redis so we don't fetch the same data again for every device. A state machine tracks each device through erase, transfer and verify. If a device drops mid-upgrade, its state is saved, so it resumes from the last acknowledged chunk instead of starting over. Callbacks are idempotent because they're keyed on device plus chunk, so a repeated callback does nothing. After repeated failures a device is blacklisted.

**"How does your circuit breaker work?"**
It has three states. Closed means requests flow normally. After too many failures it goes Open and rejects requests immediately instead of waiting for timeouts. After a cooldown it goes Half-open and lets one request through as a test. If that succeeds it closes again. The point is that a dead dependency doesn't tie up all my workers.

**"Why did you move parser config from the database to CSV files?"**
In the database there was no history and no validation — someone could change a parser config and nobody would know. In version control, every change goes through a pull request, gets reviewed, and CI validates it against stored test data before it reaches staging.

**"How do you test your code?"** *(Job description mentions this twice — prepare it.)*
Coverage is uneven across our services. For the parts I own, I test business logic against interfaces using fakes. For anything with timeouts or TTLs, I inject a clock interface so I can control time in tests instead of using sleeps. What I'd want to improve is integration testing — spinning up real Postgres, Redis and Kafka with testcontainers. Right now that's thinner than it should be.

*This is honest and shows you know what good looks like. Don't claim perfect testing.*

---

# PART 4 — TECHNICAL TOPICS

## Go — language basics

**Pointer receiver vs value receiver**
A value receiver gets a copy, so changes don't stick. A pointer receiver works on the original. Use a pointer when you need to change something, when the struct is big, or when it holds a mutex.

**Method sets** ⭐
Only `*T` can use pointer-receiver methods. So `*T` can satisfy more interfaces than `T`. If a method has a pointer receiver, the plain value does not implement that interface — only the pointer does. This is the most common "why won't this compile" error in Go.

**How slices work**
A slice is three things: a pointer to an array, a length, and a capacity. When you append and there's still capacity, it writes into the same array. When capacity runs out, Go creates a bigger array and copies everything over. After that the old and new slices no longer share memory.

**Slice aliasing problem**
Two slices can point to the same array. Changing one changes the other. This bites you in backtracking code — you must copy a slice before saving it into a results list, otherwise every saved item points to the same changing array.

**Nil interface vs nil pointer** ⭐ *(very commonly asked)*
An interface holds two parts: a type and a value. If you return a nil pointer as an error, the type part is still filled in. So the interface itself is not nil, and `if err != nil` becomes true even though the pointer is nil. The fix is to return plain `nil`, not a typed nil pointer.

**Maps and concurrency**
Maps are not safe for concurrent use. Reading at the same time is fine, but reading while writing crashes the program. Protect it with a mutex. Use `sync.Map` only when you have many reads, few writes, and different keys.

**Map order**
Iteration order is random on purpose, so people don't depend on it. If you need order, collect the keys and sort them.

**defer**
Deferred calls run when the function returns, in reverse order, and they also run during a panic. Important detail: arguments are evaluated at the moment you write `defer`, not when it runs. Defers inside a loop pile up until the function ends, so wrap the loop body in a small function.

**Error handling**
Return errors as values. Add context by wrapping with `%w`. Use `errors.Is` to check for a specific known error, and `errors.As` to pull out a specific error type so you can read its fields.

**Stack vs heap**
The compiler decides. If a value escapes the function — you return it, a goroutine captures it, or you put it in an interface — it goes to the heap. Otherwise it stays on the stack, which is cheaper.

**Garbage collector**
Go uses a concurrent mark-and-sweep collector, designed for short pauses. `GOGC` controls how much the heap grows before the next collection. `GOMEMLIMIT` sets a soft memory limit — very useful in Kubernetes, because without it the heap can grow past the container limit and get killed.

**GOMAXPROCS**
This is how many OS threads can run Go code at once. It defaults to the number of CPUs. In containers this matters — if Go sees the host CPUs instead of the container's CPU limit, it creates too many threads and gets throttled.

**byte vs rune**
A byte is one byte of UTF-8. A rune is one full character. Indexing a string gives bytes, `range` gives runes. So `len()` returns bytes, not the number of characters you see.

**String building**
Strings can't be changed, so `+=` in a loop creates a new string every time. Use `strings.Builder` instead.

**Embedding**
Go has no inheritance. Embedding one struct in another gives you its fields and methods, but it's delegation, not inheritance. Polymorphism comes from interfaces.

## Go — concurrency

**Goroutine vs thread**
A goroutine starts with about 2KB of stack that grows as needed, and Go schedules it in user space. An OS thread has a fixed stack of several MB and switches through the kernel. That's why you can run hundreds of thousands of goroutines.

**GMP scheduler**
G is a goroutine, M is an OS thread, P is a processor context holding a queue of work. A thread needs a P to run Go code. Each P has its own queue and steals work from others when idle. If a goroutine blocks on a syscall, the thread detaches so another thread can pick up that P.

**Buffered vs unbuffered channel**
Unbuffered means the sender waits until a receiver is ready — it's a synchronisation point. Buffered means the sender can continue until the buffer is full, which helps absorb bursts.

**Channel rules**
Receiving from a closed channel returns the zero value immediately. Sending to a closed channel panics. Closing twice panics. A nil channel blocks forever — which is actually useful, because you can set a channel to nil to disable that case in a `select`.

**Who closes a channel?**
The sender, always. The receiver can't know if more data is coming. With multiple senders, use a WaitGroup and close after they all finish.

**select**
It waits on several channels and takes whichever is ready. If more than one is ready it picks randomly, so nothing gets starved. Adding `default` makes it non-blocking.

**Goroutine leak**
A goroutine that is blocked forever, usually waiting on a channel nobody will write to. It holds its stack and everything it references, so memory keeps growing. Find it by tracking `runtime.NumGoroutine()` as a metric, or reading goroutine stacks from pprof. Prevent it by giving every goroutine a way to exit — usually a context.

**context**
It carries cancellation and deadlines through your call chain. Pass it as the first argument, always `defer cancel()`, and check `ctx.Done()` inside long loops. Cancelling a parent cancels everything below it, which is how you clean up a whole request.

**Mutex vs RWMutex**
Mutex gives one goroutine access at a time. RWMutex allows many readers or one writer. RWMutex is better for read-heavy work but costs more per operation. Neither can be locked twice by the same goroutine — that deadlocks.

**WaitGroup**
Call `Add` before starting the goroutine, never inside it. Call `defer wg.Done()` inside. If you also need errors back, use `errgroup` instead.

**sync.Pool**
It reuses temporary objects to reduce allocations. It is not a cache — objects can disappear at any garbage collection, there's no TTL, and you must reset them. Using it as a cache is a common mistake.

**Worker pool**
Start N goroutines all reading from one jobs channel. Close the channel when input is done, so workers exit. Use a WaitGroup to wait for them. Add a context so you can cancel. Size N near the CPU count for CPU work, much higher for IO work.

**Limiting concurrency without a pool**
Use a buffered channel as a counter. Send a token before starting work, receive it when done. Buffer size = maximum concurrent operations.

**Race detector**
Run with `-race`. It only catches races that actually happen during that run, so run it against integration tests, not just unit tests.

**Graceful shutdown**
Order matters: stop accepting new work, finish work already in progress, cancel the context to stop background goroutines, then close database and Kafka connections last.

## Kafka

**Ordering**
Kafka only guarantees order inside one partition, never across a topic. If you need order per device, use the device ID as the key so it always goes to the same partition.

**How a message picks a partition**
`hash(key) % number_of_partitions`. This is why **adding partitions breaks ordering** — the maths changes, so a key that used to go to partition 2 might now go to partition 5, and messages for that key exist in two places.

**Consumer limit**
Each partition goes to exactly one consumer in a group. So you can never have more useful consumers than partitions. Extra consumers just sit idle. This is why you create extra partitions early.

**What causes a rebalance**
A consumer joining or leaving, missing heartbeats, taking too long between polls, or the partition count changing.

**Why rebalances hurt**
In the old protocol, everyone stops and gives up all partitions before reassignment. Slow processing causes a rebalance, which delays processing more, which causes another rebalance. Cooperative rebalancing (Kafka 2.4+) only moves the partitions that actually need moving.

**acks setting**
`acks=0` doesn't wait at all and can lose data. `acks=1` waits for the leader only. `acks=all` waits for all in-sync replicas. In production use `acks=all` with `min.insync.replicas=2` and replication factor 3 — that survives one broker dying.

**Delivery guarantees**
In real life you run at-least-once: process the message, then commit the offset. If you crash in between you get a duplicate. Exactly-once exists in Kafka but only works Kafka-to-Kafka. Anything writing to a database is at-least-once plus an idempotent consumer.

**Making a consumer idempotent**
Give each message a stable business key and either use an upsert, or keep a dedup store with a TTL. This is simpler and cheaper than Kafka transactions.

**Retention vs compaction**
Retention deletes old messages by age or size — good for event streams. Compaction keeps only the latest value for each key forever — good for device state, because you can replay the topic to rebuild current state.

**Consumer lag is growing — what do you do?**
First check if it's a spike or steady growth. Then check the consumers are actually alive and not stuck rebalancing. Then find the bottleneck: is processing slow, or are there simply not enough consumers? If consumers already equal partitions, you're partition-limited and adding consumers won't help.

**Poison message**
Retry a few times with backoff, then move it to a dead letter topic, commit the offset and continue. Never retry forever — one bad message blocks everything behind it in that partition.

**Flink** *(you don't have this — say it honestly)*
Flink is a stream processing engine. It handles windows, late data and exactly-once through checkpointing. I haven't used it. I've built windowing by hand in Go using bounded queues and in-memory state, which is a narrower version of the same idea, so I expect the concepts to transfer.

**Event time vs processing time**
Event time is when the event actually happened. Processing time is when your system received it. In IoT, devices buffer data during network outages and send it later, so you must aggregate on event time. A watermark is the system saying "I don't expect anything older than this any more" — that's what lets a window close.

**Window types**
Tumbling = fixed and non-overlapping, like every 5 minutes. Sliding = fixed size but overlapping, like a 5-minute average calculated every minute. Session = grouped by gaps in activity.

## Docker

**Container vs VM**
A VM runs its own full operating system. A container is just an isolated process sharing the host's kernel, using namespaces for isolation and cgroups for limits. That's why containers start in milliseconds.

**How to write a Go Dockerfile** ⭐ *(most likely Docker question)*
Use two stages. In the build stage, copy `go.mod` and `go.sum` first and run `go mod download`, then copy the source and build with `CGO_ENABLED=0` so you get a static binary. In the final stage use `distroless` or `scratch` and copy only the binary, plus CA certificates if you make HTTPS calls. Run as a non-root user. This takes the image from around 800MB down to about 15MB.

**Why copy go.mod first?**
Each instruction is a cached layer, and changing one invalidates everything after it. If you copy all your source before downloading dependencies, every small code change re-downloads everything.

**ENTRYPOINT — shell form vs exec form** ⚠️
If you write it as a plain string, Docker wraps it in `/bin/sh -c`. Then the shell becomes process 1, and **SIGTERM never reaches your application**. Your graceful shutdown silently stops working in Kubernetes. Always use the JSON array form.

**CMD vs ENTRYPOINT**
ENTRYPOINT is the program to run. CMD is the default arguments, which someone can override at run time.

**COPY vs ADD**
ADD also unpacks tar files and downloads URLs, which surprises people. Use COPY unless you specifically want that.

**ARG vs ENV**
ARG exists only during build. ENV stays in the running container. Neither is safe for secrets — both are visible in the image history.

**Resource limits**
Docker uses cgroups. Going over the memory limit gets your process killed. Going over the CPU limit slows you down but doesn't kill you.

## Kubernetes

**Pod, ReplicaSet, Deployment**
A Pod is one or more containers sharing a network and storage. A ReplicaSet keeps a fixed number of identical pods running. A Deployment manages ReplicaSets and gives you rolling updates and rollback. You write Deployments; the rest happens automatically.

**The three probes** ⭐
Liveness asks "is this process stuck?" — failing it restarts the container. Readiness asks "can this take traffic right now?" — failing it removes the pod from the load balancer but leaves it running. Startup gives a slow-starting app time to boot without liveness killing it.

**The classic probe mistake**
Don't make liveness check your database. If the database has a hiccup, every pod fails liveness and restarts at the same time — turning a small problem into a full outage. Dependencies belong in readiness, not liveness.

**Probes for a Kafka consumer**
Readiness should reflect whether the consumer has joined the group and is polling — so during a rebalance it just stops taking traffic. Liveness should only catch a truly stuck process, and its timeout must be longer than your worst-case processing time, otherwise you kill healthy pods that are just behind.

**Requests vs limits**
Requests are what the scheduler uses to place the pod. Limits are the hard ceiling. Going over the **memory** limit means the container is killed — exit code 137. Going over the **CPU** limit means you're slowed down, not killed. That's why CPU problems show up as strange latency instead of crashes.

**Sizing memory for a Go service**
Set `GOMEMLIMIT` slightly below the container memory limit. Go's garbage collector grows the heap until it hits a threshold, so without this hint it will grow past the container limit and get killed.

**What happens when a pod is deleted** ⭐ *(great answer — connects to your resume)*
The pod is marked Terminating. Two things then happen **at the same time**: it's removed from the load balancer, and it receives SIGTERM. Removing it from the load balancer takes a moment to spread across the cluster, so traffic can still arrive for a second or two after SIGTERM. That's why you add a small sleep in a preStop hook before shutting down. After the grace period, anything still running is force-killed. For a consumer doing long work, the grace period must be longer than your worst-case processing time.

**Deployment vs StatefulSet**
Deployment pods are interchangeable with random names. StatefulSet gives each pod a fixed name and identity, a stable DNS entry, its own persistent volume, and ordered rollout. Use it when identity or per-pod storage matters.

**Service types**
ClusterIP is internal only. NodePort opens a port on every node. LoadBalancer creates a cloud load balancer, so one per service gets expensive. Headless returns pod IPs directly instead of a single virtual IP.

**Rolling update**
`maxSurge` is how many extra pods can exist during the update. `maxUnavailable` is how many can be down. New pods must pass readiness before old ones are removed. `kubectl rollout undo` reverts.

**Autoscaling (HPA)**
It scales pods based on a metric. It needs resource requests set, otherwise CPU scaling has no baseline. For Kafka consumers, scale on **lag**, not CPU — lag is what actually tells you you're behind.

**Pod is in CrashLoopBackOff — how do you debug?**
Run `kubectl describe pod` to see events and the exit code — 137 means it ran out of memory. Run `kubectl logs --previous` to see the crashed container's output. Common causes: a missing ConfigMap or Secret, a liveness probe with too short an initial delay, an image pull failure, or a dependency not reachable at startup.

**Pod is Pending — why?**
Nothing can schedule it. Either no node has enough CPU or memory, an affinity rule can't be satisfied, a taint has no matching toleration, or a volume claim can't bind. `describe pod` states the reason directly.

## AWS

**SQS visibility timeout** ⭐ *(most commonly asked SQS question)*
When you receive a message it isn't deleted — it becomes invisible for a set time. If you delete it in time, it's gone. If you don't, it comes back and another consumer processes it again. So if your processing takes longer than the timeout, you get duplicates. Fix it by increasing the timeout or extending it while processing.

**Standard vs FIFO queue**
Standard has unlimited throughput, delivers at least once, and doesn't guarantee order — so consumers must handle duplicates. FIFO guarantees order within a message group and removes duplicates, but is limited to 300 messages per second per group.

**Long polling**
Short polling often returns empty even when messages exist. Long polling waits up to 20 seconds for a message. It's cheaper and faster — always use it.

**Dead letter queue**
Set a redrive policy with a maximum receive count. After that many failures the message moves to the DLQ automatically. Alert on DLQ depth, and keep its retention longer than the source queue.

**SQS vs SNS vs Kafka**
SQS is a work queue — one consumer handles each message. SNS is broadcast — it pushes to many subscribers with no storage or replay. Kafka is a stored log — many independent consumers, and you can replay history.

**S3**
Storage classes go from Standard (hot) to Glacier (archive). Lifecycle rules move objects automatically as they age — this is how you move old telemetry off expensive storage. Presigned URLs let a client upload directly to S3 without going through your service.

**IAM roles vs users**
A user has permanent credentials. A role is assumed temporarily and gives short-lived credentials. Always prefer roles. On EKS, IRSA links a Kubernetes service account to an IAM role, so pods get credentials without any stored keys.

**Security group vs NACL**
A security group is attached to an instance and is stateful — if you allow traffic in, the reply is automatically allowed out. It only has allow rules. A NACL is attached to a subnet, is stateless, and supports deny rules.

**Multi-AZ vs read replica**
Multi-AZ is a standby copy for failover — it does not serve reads. Read replicas do serve reads but lag slightly behind. They solve different problems.

## PostgreSQL

**Partial index** *(you use this)*
An index with a WHERE condition, so it only covers some rows. For example, allow only one active record per device while still permitting many deleted ones. A normal unique constraint can't express that, and the index stays small.

**Composite index**
An index on (a, b, c) works for queries on a, on a+b, or on a+b+c — but not on b alone. Put equality columns first and the range or sort column last.

**Reading EXPLAIN ANALYZE**
EXPLAIN shows what the planner expects. ANALYZE actually runs it and shows reality. Look for: a sequential scan where you expected an index, and a big gap between expected and actual row counts — that usually means statistics are stale.

**When indexes hurt**
Every index makes inserts, updates and deletes slower. On a high-write time-series table, too many indexes destroy write speed.

**MVCC**
Every update creates a new version of the row instead of overwriting it, and each transaction sees a consistent snapshot. So readers never block writers. The cost is dead rows piling up, which VACUUM cleans.

**Connection pooling**
Postgres creates a separate process per connection, so connections are expensive. Remember your pool is **per pod** — 20 connections × 50 pods = 1000 connections, which will overwhelm the server. Use pgbouncer at scale.

**Cursor vs offset pagination** *(you use this)*
OFFSET still reads and throws away all the skipped rows, so it gets slower on later pages, and results shift if data changes. Cursor pagination filters on the last value you saw, so it stays fast — but you can't jump to a random page.

## Redis

**Why Lua scripts are atomic** *(you use this)*
Redis runs commands one at a time on a single thread. A Lua script runs completely before anything else, so you can read a value, decide, and write in one uninterrupted step. The downside is that a slow script blocks the whole server, so scripts must be short.

**Lua vs MULTI/EXEC**
MULTI just batches commands. It can't make a decision based on what it read. If you need "check this, then decide what to write" — like reserving a device — you need Lua.

**Eviction policies**
For a cache use `allkeys-lru` or `allkeys-lfu`. The trap is using a `volatile-*` policy when your keys have no TTL — then Redis has nothing it's allowed to evict, and writes start failing.

**How expiry works**
Keys are removed lazily when accessed, plus a background job samples and clears them. So memory isn't freed the instant a key expires. If many keys expire at the same moment you get a latency spike, so add random jitter to TTLs.

**RDB vs AOF**
RDB is a snapshot — small and fast to restore, but you lose recent writes. AOF logs every write — safer, but bigger and slower to restore. Most setups use `appendfsync everysec` as a middle ground.

**Redis lock problems**
Store a unique token as the value so you only delete your own lock. Release using a Lua script that compares and deletes together, because GET then DEL isn't atomic. And the TTL is a gamble — if your work takes longer than the TTL, two clients hold the lock at once. So either extend it or make the operation idempotent.

**Cache stampede**
Many requests miss the same expired key at once and all hit the database together. Fix with a short lock so only one recomputes, or jittered TTLs so keys don't expire together.

---

# PART 5 — SHORT DESIGN QUESTIONS

**Design a Go service reading Kafka and writing to Postgres**
Three layers with interfaces between them: consumer, business logic, database. Read messages in batches and commit the offset only after the batch is written — that gives at-least-once. Use an upsert on a business key so duplicates are harmless. Thread a context through everything. On SIGTERM, stop reading, finish what's in progress, commit, then exit. Failures retry with backoff and then go to a dead letter topic.

**Design a rate limiter**
Token bucket. You have a capacity and a refill rate, and you calculate refill from the time since the last request. In one process it's a struct with a mutex and an injected clock so you can test it without sleeping. Distributed, it's a Redis Lua script that reads the token count and last refill time, calculates the refill, and decrements — all in one atomic step.

**Design a job scheduler**
Jobs in a table with a next-run time and a status. Workers claim jobs using `SELECT ... FOR UPDATE SKIP LOCKED`, which lets many workers grab different jobs without blocking each other. Each claim has a lease and a heartbeat, so if a worker dies its jobs are picked up again. Execution must be idempotent because a job can run twice.

**Track whether a million devices are online**
Each heartbeat writes a Redis key with a TTL slightly longer than the heartbeat interval. If the key exists, the device is online — expiry handles offline detection automatically, no background job needed. Keep permanent state in Postgres and treat Redis as the fast layer.

**A million devices report every minute — what breaks?** ⭐
On average that's about 16,000 writes per second, which is fine. The real problem is that devices report exactly on the minute, so you get all of them in a two-second window — roughly ten times the average. The fix is to spread reporting times randomly, or assign each device an offset. After that: write in batches, partition the table by time, and downsample old data because 90 days of raw data is about 26TB.

**How do you find a memory leak?**
First confirm it's real growth and not just the garbage collector being relaxed. Then take two heap profiles with pprof and compare them to see what's growing. Also check the goroutine count — a goroutine leak looks exactly like a memory leak, because every blocked goroutine holds its stack and everything it references.

**Making a service resilient to a flaky dependency**
Timeouts on every call. Retries with backoff and jitter, but only for errors worth retrying. A circuit breaker so a dead dependency fails fast instead of using up all your workers. Limit how many requests can go to that dependency at once. And degrade gracefully — serve stale cached data rather than an error.

---

# PART 6 — DIFFICULT QUESTIONS

**"You have 2 years, we asked for 3–5."**
> That's fair. What I'd point to is scope. I've owned complete systems end to end rather than working on pieces of someone else's design. The ping service, the command platform and the OTA system were all mine from design through production. At a small company you get that ownership early, so I think the depth compares well even if the years don't.

**"Why leave after 2 years?"**
> I'm not running from anything. I've shipped a lot in a short time, but I've reached the limit of what I can learn where I am — we're a small team, code review is light, and testing culture is thin. I want to do the same kind of work in a bigger engineering organisation.

**"Why Siemens?"**
> It's the same problem I've been working on, at a much larger scale. I've spent two years on device fleets, telemetry and command delivery. Siemens builds that as a product, with constraints I haven't faced yet — multi-tenancy, certificate management across a fleet, edge processing.

**"Can you relocate to Pune?"**
> Yes. I can relocate within [30 / 45] days. No blockers.

**Also know before the call:** your notice period, current CTC, and expected range. Don't work these out during the interview.

**Prepare four stories, two minutes each:**
1. **A hard bug you fixed** — what you saw, what you suspected, what you ruled out, the real cause, and what you changed so it can't happen again.
2. **A disagreement** with a teammate and how you settled it.
3. **Something you built that failed** and what you learned. Pick a real one.
4. **An unclear requirement from a non-technical person** — the job description asks for this and your resume shows none, so prepare it deliberately.

---

# PART 7 — QUESTIONS TO ASK THEM

Pick three or four:
- What does this team own inside Foundational Technologies — which product does it support?
- Where does Flink fit in the stack today? How much is Go versus Java?
- What does code review and testing look like day to day?
- Is this genuinely office-only, or is hybrid possible?
- What would a successful first six months look like?
- What's the hardest technical problem the team is working on now?

---

# PART 8 — WHEN YOU GET STUCK

**You don't know it:**
"I haven't worked with that directly. My understanding is [X] — is that the direction you mean?" Then stop.

**You need a moment:**
"Let me think about that for a second." Silence is fine. Filling it with noise is not.

**You realise mid-answer that you're wrong:**
"Actually, let me correct that —" and fix it. Correcting yourself looks strong, not weak.

**The question is unclear:**
Ask one clarifying question. Then pick an interpretation and say which one you're using.

**You talked too long:**
"Short version: [one sentence]."

**You have no idea:**
"I don't know that one. I'd rather look it up than guess — can we come back to it?"

**Never do this:** invent a number, claim experience you don't have, or argue when they push back. When challenged, engage with it: "That's a fair point — the trade-off there was…"

---

# PART 9 — LAST 30 MINUTES

- [ ] Test camera, microphone, internet. Keep phone hotspot ready as backup.
- [ ] Open your resume and this file. Keep water nearby.
- [ ] Notebook and pen ready for diagrams.
- [ ] Phone on silent. Close Slack, email, everything.
- [ ] Re-read the job description and Parts 1–3 of this file.
- [ ] Write your questions for them somewhere visible.
- [ ] Join five minutes early.
- [ ] **Learn nothing new after 2:30.** It won't help, and the stress will hurt.

---

**One last thing.** You've built more interesting systems in two years than many people build in five. The risk today is not that you know too little — it's that you undersell your work or talk past the answer. Be specific, be concrete, and stop when you've answered the question.

Good luck.
