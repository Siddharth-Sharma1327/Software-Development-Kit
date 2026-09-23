package main

import (
	"fmt"
	"time"
)

type MyErr struct {
}

func (e *MyErr) Error() string {
	return "boom"
}

func mightFail() error {
	var p *MyErr = nil
	return p
}

func f() (result int) {
	defer func() {
		result *= 2
	}()
	return 5
}

type Speaker interface {
	Speak() string
	Walk() string
}

type Dog struct {
}

func (d *Dog) Speak() string {
	return "woof"
}
func (d *Dog) Walk() string {
	return "Walking on 4 legs"
}

type Human struct {
}

func (h *Human) Speak() string {
	return "I'm Human"
}

func (h *Human) Walk() string {
	return "Walking on 2 legs"
}

func main() {
	fmt.Println("Hello, World!")

	fmt.Println("// TASK - 1")
	s := []int{1, 2, 3, 4, 5}
	a := s[:2]

	fmt.Println(len(a), cap(a))

	a = append(a, 99)
	fmt.Println(a)
	fmt.Println(s)

	fmt.Println("// TASK - 2")
	err := mightFail()
	fmt.Println(err == nil)

	fmt.Println("// TASK - 3")
	i := 0
	defer fmt.Println("deferred i = ", i) // LIFO rule
	i = 100
	fmt.Println("final i = ", i)

	fmt.Println("// TASK - 4")
	fmt.Println(f())

	fmt.Println("// TASK - 5")
	s1 := "héllo"
	fmt.Println(len(s1))         // 5
	fmt.Println(len([]rune(s1))) // 5
	for i := range s1 {
		fmt.Print(i, " ")
	}

	fmt.Println("// TASK - 6")
	// var m map[string]int
	m := make(map[string]int, 0)
	fmt.Println(m["x"], len(m))
	m["x"] = 1

	fmt.Println("// TASK - 7")
	ch := make(chan int, 2)
	ch <- 1
	close(ch)
	v1, ok1 := <-ch
	v2, ok2 := <-ch
	fmt.Println(v1, ok1, " | ", v2, ok2)

	fmt.Println("// TASK - 8")
	s2 := make([]int, 0, 5)
	s2 = append(s2, 1, 2, 3) // s2 = {1, 2, 3, _, _}
	t := s2[:2]              // t = {1, 2, _, _, _}

	t = append(t, 77) // t = {1, 2, 77, _, _},   s2 = {1, 2, 77, _, _}
	fmt.Println(s2, t)

	fmt.Println("// TASK - 9")
	for i := 0; i < 3; i++ {
		go func(i int) {
			fmt.Println(i)
		}(i)
		time.Sleep(3 * time.Second)
	}
	// A function that uses a variable from outside itself is called a closure.

	fmt.Println("// TASK - 10")
	var sp1 Speaker = &Dog{}
	fmt.Println(sp1.Speak())
	fmt.Println(sp1.Walk())

	var sp2 Speaker = &Human{}
	fmt.Println(sp2.Speak())
	fmt.Println(sp2.Walk())

	fmt.Println("// TASK - 11")
	a1 := [3]int{1, 2, 3} // array not slice as size is defined
	b1 := a1
	b1[0] = 99
	fmt.Println(a1, b1)

	fmt.Println("// TASK - 12")
	var s5 []int
	fmt.Println(s5 == nil, len(s5), cap(s5))
	s5 = append(s5, 1)
	fmt.Println(s5, s5 == nil)

	//nil slice vs empty slice ([]int{})? Both have len 0 and behave identically in practice, but s == nil differs, and they marshal differently in JSON — nil becomes null, empty becomes [].
}

// 1 - done
// 2 -
// 3 -
