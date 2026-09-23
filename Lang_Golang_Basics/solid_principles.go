// 3) Liskov substition principle (LSP) states that objects of a superclass should be replaceable with objects of a subclass without affecting the correctness of the program. In other words, if class B is a subclass of class A, then we should be able to replace A with B without altering the desirable properties of the program.
package main 

import (
	"fmt"
)

type Shape interface {
	Area() float64
}

func PrintArea(shape Shape) {
	fmt.Println("Area:", shape.Area())
}


type Rectangle struct {
	Width float64
	Height float64
}

func (r Rectangle) Area() float64 {
	return r.Width * r.Height 
}




type Square struct {
	SideLength float64
}

func (s Square) Area() float64 {
	return s.SideLength * s.SideLength
}







func main() {
	rect := Rectangle{Width: 5, Height: 10}
	sq := Square{SideLength: 4}

	PrintArea(rect) // Output: Area: 50
	PrintArea(sq)   // Output: Area: 16
}










// 4) Interface Segregation Principle (ISP) states that a class should not be forced to implement interfaces it does not use. In other words, an interface should have only the methods that are relevant to the implementing class. This principle encourages the creation of smaller, more focused interfaces rather than large, monolithic ones.

type Woker interface {
	DoWork()
}

type Eater interface {
	Eat()
}

type Robot struct {
}

func (r Robot) DoWork() {
}


type Human struct{
}

func (h Human) DoWork() {
	fmt.Println("Human is working")
}

func (h Human) Eat() {
	fmt.Println("Human is eating")
}

func main() {
	r := Robot{}
	h := human{}

	r.DoWork() // Robot can work but cannot eat
	h.DoWork() // Human can work
	h.Eat()    // Human can eat
}





// 5) Dependency Inversion Principle (DIP) states that high-level modules should not depend on low-level modules. Both should depend on abstractions. In other words, the details of a module should depend on the abstractions, not the other way around. This principle encourages the use of interfaces and dependency injection to decouple modules and make them more flexible and maintainable.
type Database struct{}

type Storer interface {
	Store(string)
}

func(db Database) Store(data string) {
	fmt.Println("Storing data:", data)
}

type BusinessLogic struct {
	Storer Storer
}

func (b BusinessLogic) SaveData(data string) {
	b.Storer.Store(data) 
}

func main() {
	db := Database{}
	b := BusinessLogic{Storer: db}
	b.SaveData("Some important data")
}