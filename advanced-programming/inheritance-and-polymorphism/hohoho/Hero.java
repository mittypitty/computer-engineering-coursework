public class Hero extends People {

    String type(){
        return "I AM HERO";
    }

    String power(){
        return "my power is "+getPower();
    }

    String health(){
        return "my health is "+getHealth();
    }

    String damage(int damage){
        setHealth(getHealth() - 2 * damage);
        if(getHealth() >= 100) {
            setHealth(100);
        }
        if(getHealth() <= 0) {
            setHealth(0);
        }
        //health-= (2 * damage);
        return "my health is " + getHealth();
    }

    String cocktail(int power){
        setPower(getPower() + power - 2);
        if(getPower() >= 100) {
            setPower(100);
        }
        if(getPower() <= 0) {
            setPower(0);
        }
        //this.power+=(power - 2);
        return "my power is " + getPower();
    }



}