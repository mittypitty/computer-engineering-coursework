public class Enemy extends People{

    String type(){
        return "I AM ENEMY";
    }

    String power(){
        return "my power is "+getPower();
    }
    String health(){
        return "my health is "+getHealth();
    }
    String damage(int damage){
        setHealth(getHealth() - damage);
        if(getHealth() >= 100) {
            setHealth(100);
        }
        if(getHealth() <= 0) {
            setHealth(0);
        }
        return "my health is "+getHealth();
    }
    String cocktail(int power){
        setPower(getPower() + power + 10);
        if(getPower() >= 100) {
            setPower(100);
        }
        if(getPower() <= 0) {
            setPower(0);
        }
        return "my power is "+getPower();
    }
    //حواستون باشه که میزان سلامت در ابتدا صد هست و میزان قدرت در ابتدا 50 هست و همینطور میزان این دو شاخص نمیتواند کمتر از صفر و بیشتر از صد باشد ، بنابراین اگر منفی شد باید صفر گذاشته بشه و چاپ بشه و اگر بیشتر از صد شد باید همان میزان صد گذاشته بشه و چاپ شود


}