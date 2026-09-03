public class minister extends person{
    public String ministery;


    public minister(int age, String name) {
        super(age, name);
    }

    //not royal
    @Override
    public String worship() {
        return "Dorod khoda bar Changiz bad";
    }
    @Override
    public String talk() {
        return "heil changiz";
    }
}
