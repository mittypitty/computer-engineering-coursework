public class Order {
    private Customer customer;
    private Food food;
    private String discountCode;

    public Order(Customer customer, Food food) {
        this.customer = customer;
        int temp = customer.getOrderCount() + 1;
        customer.setOrderCount(temp);
        this.food = food;
    }

    public Customer getCustomer() {
        return customer;
    }

    public void setCustomer(Customer customer) {
        this.customer = customer;
    }

    public Food getFood() {
        return food;
    }

    public void setFood(Food food) {
        this.food = food;
    }

    public String getDiscountCode() {
        return discountCode;
    }

    public void setDiscountCode(String discountCode) {
        this.discountCode = discountCode;
    }

    public double calculateCost(){
        if(discountCode == DiscountCode.TWENTY_FIVE_PERCENT_CODE) {
            return food.getPrice() - food.getPrice() * 0.25;
        }
        else if(discountCode == DiscountCode.FIFTEEN_PERCENT_CODE) {
            return food.getPrice() - food.getPrice() * 0.15;
        }
        else if(discountCode == DiscountCode.TEN_PERCENT_CODE) {
            return food.getPrice() - food.getPrice() * 0.1;
        }
        else{
            return food.getPrice();
        }
    }

    public boolean hasDeliveryFee(){
        if(customer.getOrderCount() > 2) {
            customer.setOrderCount(0);
            return false;
        }
        else return true;
    }


    public String toString() {
        String orderList = "Order " + food.getName() + " by " + customer.getName() + " has delivery. Delivery fee is ";
        if(hasDeliveryFee()) {
            orderList += "not free";
        }
        else {
            orderList += "free";
        }
        return orderList;
    }

}
