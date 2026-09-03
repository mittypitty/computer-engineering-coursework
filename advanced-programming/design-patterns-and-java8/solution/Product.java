import java.util.List;
import java.util.stream.Collectors;
import java.util.ArrayList;
import java.util.*;
import java.util.stream.*;

public class Product {
    private String name;
    private double price;
    private double discount;
    private String category;

    public Product(String name, double price, double discount, String category) {
        this.name = name;
        this.price = price;
        this.discount = discount;
        this.category = category;
    }

    public double getDiscountedPrice() {
        return price - (discount / 100 * price);
    }
    public double getDiscount() {
        return discount;
    }
    public String getCategory() {
        return category;
    }

    public static List<Product> categoryBasedDiscount(List<Product> list, double minDiscount, String category) {
        return list.stream().filter(pr -> pr.getCategory().equals(category) && pr.getDiscount() >= minDiscount)
                .sorted(Comparator.comparingDouble(Product::getDiscountedPrice)).collect(Collectors.toList());
    }


    public static double averageDiscountedPrice(List<Product> list, String category) {
        return list.stream().filter(pr -> pr.getCategory().equals(category))
                .mapToDouble(Product::getDiscountedPrice).average().orElse(0.0);
    }


    public static List<Product> sortedList(List<Product> list) {
        return list.stream()
                .sorted(Comparator.comparingDouble(Product::getDiscountedPrice))
                .collect(Collectors.toList());
    }

}
