// Run with: java 4.DecoratorDesignPattern.java
// (the class containing main must be the first class in the file)

// Client code
class CoffeeShopDemo {
    public static void main(String[] args) {

        // Order 1: Simple coffee
        Coffee order1 = new SimpleCoffee();
        System.out.printf("Order 1: %s | $%.2f%n",
            order1.getDescription(), order1.getCost());

        // Order 2: Coffee with milk and sugar
        Coffee order2 = new SugarDecorator(new MilkDecorator(new SimpleCoffee()));
        System.out.printf("Order 2: %s | $%.2f%n",
            order2.getDescription(), order2.getCost());

        // Order 3: Coffee with double milk, sugar and whipped cream
        Coffee order3 = new WhippedCreamDecorator(new SugarDecorator(new MilkDecorator(new MilkDecorator(new SimpleCoffee()))));
        System.out.printf("Order 3: %s | $%.2f%n",
            order3.getDescription(), order3.getCost());
    }
}

// Component interface
interface Coffee {
    double getCost();
    String getDescription();
}

// Concrete component
class SimpleCoffee implements Coffee {
    @Override
    public double getCost() {
        return 1.00;
    }

    @Override
    public String getDescription() {
        return "Simple Coffee";
    }
}

// Abstract decorator
abstract class CoffeeDecorator implements Coffee {
    protected final Coffee inner;

    public CoffeeDecorator(Coffee inner) {
        this.inner = inner;
    }
}

//Concrete Decorators 
class MilkDecorator extends CoffeeDecorator {
    public MilkDecorator(Coffee inner) {
        super(inner);
    }

    @Override
    public double getCost() {
        return inner.getCost() + 0.50;
    }

    @Override 
    public String getDescription() {
        return inner.getDescription() + ", milk";
    }
}


class SugarDecorator extends CoffeeDecorator {
    public SugarDecorator(Coffee inner) {
        super(inner);
    }

    @Override
    public double getCost() {
        return inner.getCost() + 0.20;
    }

    @Override 
    public String getDescription() {
        return inner.getDescription() + ", sugar";
    }
}

class WhippedCreamDecorator extends CoffeeDecorator {
    public WhippedCreamDecorator(Coffee inner) {
        super(inner);
    }

    @Override
    public double getCost() {
        return inner.getCost() + 1.00;
    }

    @Override
    public String getDescription() {
        return inner.getDescription() + ", whipped cream";
    }
}
