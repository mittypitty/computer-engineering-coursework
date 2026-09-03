import java.util.*;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.*;

public class Branch {

    private int id;
    private List<Car> cars = new ArrayList<>();


    public Branch(int id) {
        this.id = id;
    }


    public void addCar(Car car) {
        if (cars.contains(car) ) {

        }
        else {
            cars.add(car);
        }
    }

    public Car getMostExpensiveCar() {
        return cars.stream()
                .max(Comparator.comparingInt(Car::getPrice)).orElse(null);
    }

    public Brand getMostWorthBrand() {
        return cars.stream()
                .collect(Collectors.groupingBy(Car::getBrand, Collectors.summingInt(Car::getPrice)))
                .entrySet().stream().max(Map.Entry.comparingByValue()).map(Map.Entry::getKey)
                .orElse(null);
    }

    public void increasePrice(Brand brand, int add) {
        cars.stream()
                .filter( car -> car.getBrand() == brand ).forEach( car -> car.setPrice( car.getPrice() + add ) );
    }

    public List<Car> getCars(Color color, Brand brand) {
        return cars.stream()
                .filter( car -> car.getColor() == color && car.getBrand() == brand ).collect( Collectors.toList() );
    }



    public List<Car> getCars() {
        return cars;
    }
    public void setId(int id) {
        this.id = id;
    }
    public void setCars(List<Car> cars) {
        this.cars = cars;
    }

}
