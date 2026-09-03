class Vehicle {
    public String echelons;

    public Vehicle() {
        echelons = "Vehicle";
    }
}
class landVehicle extends Vehicle{

    public landVehicle(){
        echelons += " > Land Vehicle";
    }
}
class airVehicle extends Vehicle{

    public airVehicle() {
        echelons += " > Air Vehicle";
    }
}
class fourWheels extends landVehicle{

    public fourWheels() {
        echelons += " > Four Wheels";
    }
}
class twoWheels extends landVehicle{

    public twoWheels() {
        echelons += " > Two Wheels";
    }
}
class Motorcycle extends twoWheels{


    public Motorcycle(){
        echelons += " > Motorcycle";
    }
}
class Car extends fourWheels{

    public Car(){
        echelons += " > Car";
    }
}
class Jet extends airVehicle{

    public Jet(){
        echelons += " > Jet";
    }
}
class Bicycle extends twoWheels{

    public Bicycle(){
        echelons += " > Bicycle";
    }
}
