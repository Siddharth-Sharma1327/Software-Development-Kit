// 1) Single Responsibility Principle (SRP): A class should have only one reason to change, meaning it should have only one job or responsibility. This principle helps in making the code more maintainable and understandable.

class Marker {
    String name;
    String color;
    int year;
    int price;

    public Marker(String name, String color, int year, int price) {
        this.name = name;
        this.color = color;
        this.year = year;
        this.price = price;
    }
}


class Invoice {
    private Marker marker;
    private int quantity;

    public Invoice(Marker marker, int quantity) {
        this.marker = marker;
        this.quantity = quantity;
    }

    public int caclulateTotal() {
        int price = ((marke.price) * this.quantity);
        return price;
    }

    // any chnage in below two functions will lead to change in Invoice class which is not good as per SRP principle. So we can create another class for these two functions.
    public void printInvoice() {
        // print invoice
    }

    public void saveToDB() {
        // save data into db
    }
}



// Soution:-
class Invoice {
    private Marker marker;
    private int quantity;

    public Invoice(Marker marker, int quantity) {
        this.marker = marker;
        this.quantity = quantity;
    }

    public int caclulateTotal() {                 // only one reason to change class
        int price = ((marke.price) * this.quantity);
        return price;
    }
}

class InvoicePrinter {
    private Invoice invoice;

    public InvoicePrinter(Invoice invoice) {
        this.invoice = invoice;
    }

    public void printInvoice() {
        // print invoice
    }
}


class InvoiceDao {
    private Invoice invoice;

    public InvoiceDao(Invoice invoice) {
        this.invoice = invoice;
    }

    public void saveToDB() { 
        // save data into db
    }
}
// each class has single resposibility and any change in one class will not affect other classes.





// 2) Open/Closed Principle (OCP): Software entities (classes, modules, functions, etc.) should be open for extension but closed for modification. This means that the behavior of a module can be extended without modifying its source code.

class InvoiceDao {
    private Invoice invoice;

    public InvoiceDao(Invoice invoice) {
        this.invoice = invoice;
    }

    public void saveToDB() { 
        // save data into db
    }

    public void saveToFile(String fileName) {  // X X
        // save data into file
    }
}


// Solution:-
interface InvoiceDao {
    public void save(Invoice invoice);
}

class DatabaseInvoiceDao implements InvoiceDao {

    @Override
    public void save(Invoice invoice) {
        // save to DB
    }
}

class FileInvoiceDao implements InvoiceDao {

    @Override
    public void save(Invoice invoice) {
        // save to file
    }
}




// 3) Liskov Substitution Principle (LSP): Objects of a superclass should be replaceable with objects of its subclasses without affecting the correctness of the program. In other words, subclasses should be able to extend the functionality of a superclass without changing its behavior. 

interface Bike {
    void turnOnEngine();
    void accelerate();
}

class MotorCycle implements Bike {

    private boolean isEngineOn;
    private int speed;

    public void turnOnEngine() {
        this.isEngineOn = true;
    }

    public void accelerate() {
        this.speed += 10;
    }
}

class Bicycle implements Bike {   // X X

    private int speed;

    public void turnEngineOn() {      // narrowed down the functionality of the parent class which is not good as per LSP principle.
        throw new AssertionError("Bicycle does not have an engine");
    }

    public void accelerate() {
        this.speed += 5;
    }
}





//  4) Interface Segregation Principle (ISP): Clients should not be forced to depend on interfaces they do not use. This principle encourages the creation of smaller, more specific interfaces rather than large, general-purpose ones.

interface RestaurantEmployee {
    void washDishes();
    void serveCustomer();
    void cookFood();
}


class waiter implements RestaurantEmployee {
    public void washDishes() {   // XX
        // not my job
    }

    public void serveCustomer() {
        System.out.println("Serving customer"); 
    }

    public void cookFood() {    // XX
        // not my job
    }
}


// Solution:-

interface WaiterInterface {
    void serveCustomer();
    void takeOrder();
}

interface ChefInterface() {
    void cookFood();
    void decideMenu();
}


class waiter implements WaiterInterface {      // doesnt have to implement unnecessary methods

    public void serveCustomer() {
        System.out.println("Serving customer");
    }

    public void takeOrder() {
        System.out.println("Taking order");
    }
}


// 5) Dependency Inversion Principle (DIP): High-level modules should not depend on low-level modules. Both should depend on abstractions (e.g., interfaces). This principle promotes the use of interfaces or abstract classes to decouple high-level and low-level components, making the system more flexible and easier to maintain.

class Macbook {     // wrong as per DIP principle as it is dependent on low level modules WiredKeyboard and WiredMouse. So if we want to change the keyboard or mouse then we have to change the Macbook class which is not good.
    private final WiredKeyboard keyboard;
    private final WiredMouse mouse;

    public Macbook() {
        this.keyboard = new WiredKeyboard();
        this.mouse = new WiredMouse();
    }
}


// Solution:-
interface Keyboard {
    void type();
}

interface Mouse {
    void click();
}


class Macbook {
    private final Keyboard keyboard;
    private final Mouse mouse;

    public Macbook(Keyboard keyboard, Mouse mouse) {
        this.keyboard = keyboard;
        this.mouse = mouse;
    }
}




// Liskov Substitution Principle (LSP): Objects of a superclass should be replaceable with objects of its subclasses without affecting the correctness of the program. In other words, subclasses should be able to extend the functionality of a superclass without changing its behavior.

public class Vehicle {
    public Integer getNumberOfWheels() {
        return 2;
    }
}

public class EngineVehicle extends Vehicle {
    public boolean hasEngine() {
        return true;
    }
}

public class Bicycle extends Vehicle {
    @Override
    public Integer getNumberOfWheels() {
        return 2;
    }
}

public class Car extends EngineVehicle {
    @Override
    public Integer getNumberOfWheels() {
        return 4;
    }
}

public class Motorcycle extends EngineVehicle {
    @Override
    public Integer getNumberOfWheels() {
        return 2;
    }
}


public class Main {
    public static void main(String args[]) {
        List<EngineVehicle> vehicleList = new ArrayList<>();
        vehicleList.add(new Car());
        vehicleList.add(new Motorcycle());
        // bicycle cannot be added to list

        for (EngineVehicle vehicle : vehicleList) {
            System.out.println("Number of wheels: " + vehicle.getNumberOfWheels());
            System.out.println("Has engine: " + vehicle.hasEngine());
        }
    }
}