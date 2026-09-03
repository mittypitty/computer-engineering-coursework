
public class Car {
    private String model;
    private int price;
    private Color color;
    private Brand brand;



    public Car(String model, int price, Brand brand, Color color) {
        this.model = model;
        this.price = price;
        this.color = color;
        this.brand = brand;

    }


    public String getModel() {
        return model;
    }
    public Brand getBrand() {
        return brand;
    }
    public Color getColor() {
        return color;
    }
    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    public void setBrand(Brand brand) {
        this.brand = brand;
    }
}

enum Brand{Benz, BMW, Porche}
enum Color{Red, Blue, Green, Black, White}