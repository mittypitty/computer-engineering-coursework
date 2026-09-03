import java.util.*;

public class Mabna {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int n1 = input.nextInt();
        int mabna = n1 % 10;
        System.out.print(n1);
        for(int i = 1; i < n; i++) {
            int finalnum = 0;
            int firstnum = input.nextInt();
            int firstnum1 = firstnum;
            int x = 0; 
            while(firstnum > 0) {
                finalnum = ((firstnum) % 10) * Power(mabna, x) + finalnum;
                x++;
                firstnum = firstnum / 10;
            }
            System.out.print(finalnum);
            mabna = finalnum % 10; 
        }
    }

public static int Power(int base, int exp)
    {
        if (exp == 0) {
            return 1;
        }
        int result = base;
        for(int i = 1; i < exp; i++) {
            result *= base;
        } 
        return result;
    }
}