import java.util.*;
public class Bityab {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int k = input.nextInt();
        String finalstr = mainFunc(n);
        char ch = finalstr.charAt(k - 1);
        //System.out.print(S(3));
        System.out.print(ch);
    }
    public static String operator(String x) {
        int tool = x.length();
        //invert
        String y = "";
        int i = tool - 1;
        while(i >= 0) {
            if(x.charAt(i) == '0') {
                y = "1" + y;
            }
            else if(x.charAt(i) == '1') {
                y = "0" + y;
            }
            i--;
        }
        String z = "";
        int j = tool - 1 ;
        while (j >= 0) {
            if(y.charAt(j) == '0') {
                z = z + "0";
            }
            else if(y.charAt(j) == '1') {
                z = z + "1";
            }
            j--;
        }
        return z;
    }
    public static String mainFunc(int w) {
        if(w == 1) {
            return "0";
        }
        String str = mainFunc(w - 1) + "1" + operator(mainFunc(w - 1));

        return str; 
    }
}