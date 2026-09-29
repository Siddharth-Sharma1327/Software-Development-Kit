# Go Questions for L1 — Practice List

Two parts. **Part A** is questions to answer out loud. **Part B** is code-output puzzles — the format L1 interviewers actually use to separate people who write Go from people who've read about Go. All outputs in Part B are verified on Go 1.22.

---

# PART A — QUESTIONS TO ANSWER OUT LOUD

Tick each one you can answer in under 90 seconds without looking.

## Tier 1 — near-certain (do all of these)

- [ ] What is a goroutine? Why is it cheaper than an OS thread?
- [ ] Concurrency vs parallelism. Give a real example from your work.
- [ ] Buffered vs unbuffered channel — when do you use each?
- [ ] What happens when you send to a closed channel? Receive from one? Close it twice?
- [ ] Who should close a channel, and why?
- [ ] How does `select` work? What does `default` do?
- [ ] How do slices work internally? What happens on `append`?
- [ ] Array vs slice.
- [ ] `byte` vs `rune`. Why doesn't `len()` match visible characters?
- [ ] Are maps safe for concurrent use? What do you do instead?
- [ ] How does `defer` work? When are its arguments evaluated?
- [ ] `sync.Mutex` vs `sync.RWMutex`.
- [ ] What is `sync.WaitGroup` for? What's the common bug?
- [ ] What is a race condition? How do you detect and prevent one?
- [ ] How do interfaces work in Go? What does implicit satisfaction mean?
- [ ] How does Go handle errors? What does `%w` do?
- [ ] `errors.Is` vs `errors.As`.
- [ ] What is `context` for? How do you use it?
- [ ] Value receiver vs pointer receiver — how do you choose?
- [ ] Functions vs methods.

## Tier 2 — likely, especially "Go internals" flavour

- [ ] Explain the GMP scheduler.
- [ ] How does Go's garbage collector work? (tri-colour mark and sweep)
- [ ] Stack vs heap — how does the compiler decide? (escape analysis)
- [ ] What is `GOMAXPROCS`? What breaks in containers?
- [ ] What are method sets? Why does `*T` satisfy more interfaces than `T`?
- [ ] Why can a non-nil interface hold a nil pointer?
- [ ] What is a goroutine leak? How do you find one?
- [ ] How do you gracefully shut down a Go service?
- [ ] How do you bound concurrency? (worker pool / semaphore)
- [ ] How do you implement a timeout correctly?
- [ ] Go has no inheritance — how do you get code reuse?
- [ ] How do you achieve OOP features in Go?
- [ ] `panic` vs `log.Fatal` vs returning an error.
- [ ] `make` vs `new`.
- [ ] What is `sync.Once` for?
- [ ] When would you use atomics instead of a mutex?

## Tier 3 — deeper probes

- [ ] What is `sync.Pool`, and when is it misused?
- [ ] What causes a deadlock in Go?
- [ ] Why is map iteration order random?
- [ ] What is a nil channel useful for?
- [ ] What are generics good for? When do you avoid them?
- [ ] What is the zero value principle?
- [ ] How do you structure a production Go service?
- [ ] How do you test code that involves timeouts or TTLs?
- [ ] Fan-in and fan-out.

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

# PART C — CODE TO WRITE

Write each from scratch, no reference. Compile and run them.

**Tier 1 — most likely asks**
- [ ] Worker pool: N goroutines, jobs channel, results channel, `WaitGroup`, context cancellation, clean exit
- [ ] Two goroutines printing alternately (odd/even) using channels
- [ ] Bounded concurrency using a buffered channel as a semaphore
- [ ] Graceful shutdown: `signal.NotifyContext`, drain, exit

**Tier 2**
- [ ] Fan-in: merge N channels into one
- [ ] Rate limiter (token bucket) with mutex and an injected clock
- [ ] Thread-safe counter / cache with `RWMutex`
- [ ] Timeout using `context.WithTimeout` and `select`

**DSA in Go — from the patterns in your research**
- [ ] Longest substring without repeating characters (sliding window + `map[rune]int`)
- [ ] Two sum (hashmap, O(n))
- [ ] Valid anagram / palindrome (rune handling)
- [ ] Reverse a linked list (iterative and recursive)
- [ ] Detect cycle in a linked list (fast/slow pointers)
- [ ] Find middle of a linked list
- [ ] Sort 0s, 1s, 2s in place (Dutch national flag)
- [ ] Number of islands (BFS/DFS on a grid)
- [ ] Binary tree level order traversal (queue)

Given your contest background these are all well within reach — practise **writing them in Go**, not the algorithms.

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

# TONIGHT'S ORDER

1. Part B puzzles — 30 min. Highest value, least covered elsewhere.
2. Part A Tier 1 out loud — 45 min. Mark anything you stumble on.
3. Worker pool from memory, compiled and run — 20 min.
4. Part A Tier 2 — 30 min.
5. Two DSA problems in Go, timed — 30 min.

Stop by 10pm. Tomorrow morning: re-read Part B and rewrite the worker pool. Nothing new.
