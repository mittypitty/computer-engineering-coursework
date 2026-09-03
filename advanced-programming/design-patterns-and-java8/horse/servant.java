public class servant extends person {

    //not final
    public int remainAges;


    public servant(int age, String name) {
        super(age, name);
    }

    @Override
    public String worship() {
        return "Dorod khoda bar Changiz bad";
    }
    @Override
    public String talk() {
        return "heil changiz";
    }
}



