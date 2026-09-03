public class Engine {
    private  int numberOfCilinders;
    private  char engineConfiguration;
    private  int horsePower;
    private  boolean isTurboCharged;
    Engine(int numberOfCilinders, char engineConfiguration, int horsePower, boolean isTurboCharged) {
        this.numberOfCilinders = numberOfCilinders;
        this.engineConfiguration = engineConfiguration;
        this.horsePower = horsePower;
        this.isTurboCharged = isTurboCharged;
    }
    public int getNumberOfCilinders() {
        return numberOfCilinders;
    }
    public char getEngineConfiguration() {
        return engineConfiguration;
    }
    public int getHorsePower() {
        return horsePower;
    }
    public boolean getIsTurboCharged() {
        return isTurboCharged;
    }
    public void setNumberOfCilinders(int numberOfCilinders) {
        this.numberOfCilinders = numberOfCilinders;
    }
    public void setEngineConfiguration(char engineConfiguration) {
        this.engineConfiguration = engineConfiguration;
    }
    public void setHorsePower(int horsePower) {
        this.horsePower = horsePower;
    }
    public void setIsTurboCharged(boolean isTurboCharged) {
        this.isTurboCharged = isTurboCharged;
    }
}
