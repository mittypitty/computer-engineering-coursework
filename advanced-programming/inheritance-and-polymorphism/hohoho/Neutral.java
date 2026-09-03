public class Neutral extends People{

    String type(){
        return "I AM NEUTRAL";
    }

    String power(){
        return "my power is "+getPower();
    }

    String health(){
        return "my health is "+getHealth();
    }

    String damage(int damage){
        return "ERROR";
    }

    String cocktail(int power){
        return "ERROR";
    }


}
