public class Car {
    private static Car[] cars = new Car[100];
    public static int numberOfCars = 0;
    private Wheel[] wheels = new Wheel[4];
    private Engine engine;
    private String vinNumber;    
    public Car(Engine engine, String vinNumber) {
        this.engine = engine;
        this.vinNumber = vinNumber;
        cars[numberOfCars] = this;
        numberOfCars++;
    }
    public void setWheels(Wheel w1, Wheel w2, Wheel w3, Wheel w4){
        wheels[0] = w1; wheels[1] = w2; wheels[2] = w3; wheels[3] = w4;
    }
    public static Car[] getCars() {
        return cars;
    }   
    public Wheel[] getWheels() {
        return wheels;
    }    
    public Engine getEngine() {
        return engine;
    }
    public String getVinNumber() {
        return vinNumber;
    }
    public static int getNumberOfCars() {
        return numberOfCars;
    }    

    public String getEngineSummery(){
        String engineSummary = "";
        if(getEngine().getIsTurboCharged()) {
            engineSummary  += "turbo charged ";
        }
        engineSummary += getEngine().getEngineConfiguration() +"" + getEngine().getNumberOfCilinders() + " " + "with" + " " + getEngine().getHorsePower() + " " + "horse powers";
        return engineSummary;
    }    
    
    public boolean areWheelsBalanced(){
        int i = 0;
        while (i < 4) {
            if(wheels[0].getTireSize() != wheels[i].getTireSize()) {
                return false;
            }
            i+=1;
        }
        return true;
    }

    public static void clear(){
        numberOfCars = 0;
        //delete cars[]
        Car[] cars = new Car[100];
    }
}
