import java.util.stream.Stream;

public class Function<T> {
    private String message;
    private T input;
    
    public T getInput() {
        // Todo
        return input;
    }
    
    public String getMessage() {
        // Todo
        return message;
    }
    
    public void setInput(T input) {
        this.input = input;
    }
    
    public void setMessage(String message) {
        this.message = message;
    }
    
    public Function(T input) {
        this.input = input;
        //message = " ";
        this.message = " ";
    }
    
    public void compile() {
        // Todo

        if(input instanceof Double) {
             message =  "IT'S DOUBLE AND MY OUTPUT IS NOTHING";
        }

        else if(input instanceof Integer) {
            int sum= 0;
            int remain = 0;
            int number = (int) input;

            int numberCopy = number;
            while(numberCopy > 0) {
                sum += numberCopy % 10;
                numberCopy /= 10;
            }

            remain = number % sum;
            message = "IT'S INTEGER AND MY OUTPUT IS " + remain;
        }

        else if(input instanceof String) {
            int countA = 0;
            int countS = 0;
            String str = (String) input;

            for(int i = 0; i < str.length(); i++){
                if (str.charAt(i) == 'a') {
                    countA++;
                }
                else if(str.charAt(i) == 's') {
                    countS++;
                }
            }

            message = "IT'S STRING AND MY OUTPUT IS " + (countA - countS);
        }

        System.out.println(message);
    }
}
