abstract class People{
    private int health;
    private int power;
    People(){
        this.power=50;
        this.health=100;
    }
    String type(){
        return "i don't have any type";
    }

    String power(){
        return "my power is "+power;
    }
    String health(){
        return "my health is "+health;
    }

    String damage(int damage){
        health-=damage;
        return "my health is"+health;
    }
    String cocktail(int power){
        this.power+=power;
        return "my power is "+power;
    }

    public int getHealth() {
        return health;
    }

    public void setHealth(int health) {
        this.health = health;
    }

    public int getPower() {
        return power;
    }

    public void setPower(int power) {
        this.power = power;
    }
}
