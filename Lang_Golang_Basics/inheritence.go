package main 
import(
	"fmt"
)

// Inheritence is not supported in golang its achieved by composition

type Person struct {
	Name string
	Age int
}


func NewPerson(name string, age int) *Person {
	return &Person{
		Name: name,
		Age: age,
	}
}

func(p *Person) Intro() {
	fmt.println("My name is", p.Name, "and I am", p.Age, "years old.")
}

type Employee struct {
	*Person
	EmpployeeID int
}

func(e *Employee) Intro() {
	fmt.println("My name is", e.Name, "and I am", e.Age, "years old. My employee ID is", e.EmpployeeID)
}

func main() {
	p := &Person{
		Name: "John",
		Age: 30,
	}
	ee := Employee{
		Person: p,
		EmployeeID: 12345,
	}
	ee.Person.Intro()
	ee.Intro()
	p.Intro()
}


// class/object -> struct/methods
// contructor -> function returning pointer to struct
// encapsulation -> first letter of method to be Capittal for public and small letter for private
// inheritance -> acheived by composition
// abstraction ->
// polymorphism -> 
