public abstract class person implements aliveCreature{


    private final int age;
    private final String name;

    public person(int age,String name){
        this.name = name;
        this.age = age;
    }


    public int getAge() {
        return age;
    }


    public String getName() {
        return name;
    }


    public abstract String talk();
}
