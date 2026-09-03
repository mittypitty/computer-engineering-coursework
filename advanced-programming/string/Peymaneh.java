import java.util.*;
public class Peymaneh {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        long n;
        n = input.nextLong();
        long m;
        m = input.nextLong();
        long peymane = 1000000007 ; 
        long n2 = 1;
        n = n % peymane;
        do {
            if(m % 2 == 1) {
                n2 = (n2 * n) % peymane;
            }
            n = (n * n) % peymane;
            m = m / 2;
            
        } while (m >= 1);

        System.out.println(n2);
    }
}