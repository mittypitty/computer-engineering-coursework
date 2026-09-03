public class Royal extends person{


    public int royalRate;


    public Royal(int age, String name, int royalRate) {
        super(age, name);
        this.royalRate = royalRate;
        //1 for king and 2 for the other
    }

    //worship == null

    @Override
    public String worship() {
        return null;
    }
    @Override
    public String talk() {
        return "HEIL CHANGIZ";
    }
}

