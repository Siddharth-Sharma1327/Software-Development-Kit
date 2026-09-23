// a function that returns a function -> used for data isolation
package main

import (
	"fmt"
)

func ASum() func() {
	var sum = 0
	return func() {
		sum +=1
		fmt.Println(sum)
	}
}

func main() {
	b := ASum()
	b()
	b()
	b()
	b()
	c := ASum()
	c()
}

// a function which access and updates the variable of the outer function is called closure i.e out of its scope variable
