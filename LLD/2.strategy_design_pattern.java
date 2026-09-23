// Without strategy pattern


public class Vehicle() {
    public void drive() {
        System.out.println("Nomral Driving Capability");
    }
}


public class SportsVerhicle extends Vehicle {

    @Override
    public void drive(){
        System.out.println("Sports Vehicle Driving Capability");
    }
}

public class PassengerVehicle extends Vehicle {
}


public class OfftroadVehicle extends Vehicle {

    @Override
    public void drive(){
        System.out.println("Sports Vehicle Driving Capabilit");
    }
}





// Solution:-

public interface DriveStrategy {
    public void drive(); 
}

public class NormalDriveStrategy implements DriveStrategy {
    @Override
    public void drive() {
        System.out.println("Normal Driving Capability");
    }
}

public class SportsDriveStrategy implements DriveStrategy {
    @Override
    public void drive() {
        System.out.println("Sports Vehicle Driving Capability");
    }
}



public class Vehicle {
    DriveStrategy driveObject;

    // this is known as constructor injection, we are injecting the dependency through constructor
    Vehicle(DriveStrategy driveObject) {
        this.driveObject = driveObject;
    }

    public void drive() {
        driveObject.drive();
    }
}

public class OffroadVehicle extends Vehicle {

    OffroadVehicle() {
        super(new SportsDriveStrategy());      // super - calls the constructor of base class
    }
}

public class SportsVehicle extends Vehicle {

    SportsVehicle() {
        super(new SportsDriveStrategy());
    }
}

public class PassengerVehicle extends Vehicle {

    PassengerVehicle() {
        super(new NormalDriveStrategy());
    }
}


public class Main {
    public static void main(String []args) {
        Vehicle vehicle = new SportsVehicle();
        vehicle.drive();
    }

}