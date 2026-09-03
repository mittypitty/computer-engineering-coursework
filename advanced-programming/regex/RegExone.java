import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.*;

public class RegExone {
    public static void main(String[] args) {
        String[] x;
        String x1, x2, x3;
        int number1, number2;
        String javab = " ";
        Scanner input = new Scanner(System.in);
        String moadele = input.nextLine();

        Pattern pattern1 = Pattern.compile("\\d+ [+] \\d+ [=]\\s+\\d+.*");
        Matcher matcher = pattern1.matcher(moadele);

        x = moadele.split("[+=]");
        x1 = x[0].trim();
        x2 = x[1].trim();
        x3 = x[2].trim();

        //Seprate
        Pattern hash1 = Pattern.compile("\\d*[#]\\d* [+] \\d+ [=] \\d+\\s*"); 
        Matcher matcher1 = hash1.matcher(moadele);

        if(matcher1.find()) {
            x[0] = x1;
            x[1] = x2;
            x[2] = x3;
            number1 = Integer.parseInt(x[1]);
            number2 = Integer.parseInt(x[2]);
            javab = Integer.toString(number2 - number1);
            //System.out.println(x[0]);
            //System.out.println(x[1]);
            //System.out.println(x[2]);
            int index1 = x[0].length() - 1;
        boolean bool = true;

        for(int i = 0, j = 0 ; x[0].charAt(j) != '#' ; i++) {
            if (javab.charAt(j) != x[0].charAt(i)) {
            bool = false;
            }
            j++;
        }
        
        int index2 = javab.length() - 1;
        boolean bool2 = true;

        for (int i = index2; x[0].charAt(index1) != '#'; i--) {
            if (x[0].charAt(index1) != javab.charAt(i)) {
                bool2 = false;
            }
            index1--;
        } 

        int y = 1;

        if (!bool) {
            y = -1;
        }
        if (!bool2) {
            y = -1;
        }
            if(y == 1) {
                    System.out.println(javab + " + " + x[1] + " = " + x[2]);
                }
                else if(y == -1) {
                System.out.println(-1);
                }
        }
        Pattern hash2 = Pattern.compile("\\d+ [+] \\d*[#]\\d* [=] \\d+\\s*"); 
        Matcher matcher2 = hash2.matcher(moadele);
        if(matcher2.find()) {
            x[0] = x2;
            x[1] = x1;
            x[2] = x3;
            number1 = Integer.parseInt(x[1]);
            number2 = Integer.parseInt(x[2]);
            javab = Integer.toString(number2 - number1);
            //System.out.println(x[0]);
            //System.out.println(x[1]);
            //System.out.println(x[2]);
            int index1 = x[0].length() - 1;
        boolean bool = true;

        for(int i = 0, j = 0 ; x[0].charAt(j) != '#' ; i++) {
            if (javab.charAt(j) != x[0].charAt(i)) {
            bool = false;
            }
            j++;
        }
        
        int index2 = javab.length() - 1;
        boolean bool2 = true;

        for (int i = index2; x[0].charAt(index1) != '#'; i--) {
            if (x[0].charAt(index1) != javab.charAt(i)) {
                bool2 = false;
            }
            index1--;
        } 

        int y = 1;

        if (!bool) {
            y = -1;
        }
        if (!bool2) {
            y = -1;
        }
        if(y == 1) {
            System.out.println(x[1] + " + " + javab + " = " + x[2]);
        }
        else if(y == -1) {
            System.out.println(-1);
        }

        }

        Pattern hash3 = Pattern.compile("\\d+ [+] \\d+ [=] \\d*[#]\\d*\\s*"); 
        Matcher matcher3 = hash3.matcher(moadele);
        if(matcher3.find()) {
            x[0] = x3;
            x[1] = x1;
            x[2] = x2;
            number1 = Integer.parseInt(x[1]);
            number2 = Integer.parseInt(x[2]);
            javab = Integer.toString(number2 + number1);
            //System.out.println(x[0]);
            //System.out.println(x[1]);
            //System.out.println(x[2]);
            int index1 = x[0].length() - 1;
        boolean bool = true;

        for(int i = 0, j = 0 ; x[0].charAt(j) != '#' ; i++) {
            if (javab.charAt(j) != x[0].charAt(i)) {
            bool = false;
            }
            j++;
        }
        
        int index2 = javab.length() - 1;
        boolean bool2 = true;

        for (int i = index2; x[0].charAt(index1) != '#'; i--) {
            if (x[0].charAt(index1) != javab.charAt(i)) {
                bool2 = false;
            }
            index1--;
        } 

        int y = 1;

        if (!bool) {
            y = -1;
        }
        if (!bool2) {
            y = -1;
        }
            if(y == 1){
                    System.out.println(x[1] + " + " + x[2] + " = " + javab);
                }
                else if(y == -1) {
                    System.out.println(-1);
                }
        }

        // int index1 = x[0].length() - 1;
        // boolean bool = true;

        // for(int i = 0, j = 0 ; x[0].charAt(j) != '#' ; i++) {
        //     if (javab.charAt(j) != x[0].charAt(i)) {
        //     bool = false;
        //     }
        //     j++;
        // }
        
        // int index2 = javab.length() - 1;
        // boolean bool2 = true;

        // for (int i = index2; x[0].charAt(index1) != '#'; i--) {
        //     if (x[0].charAt(index1) != javab.charAt(i)) {
        //         bool2 = false;
        //     }
        //     index1--;
        // } 

        // int y = 1;

        // if (!bool) {
        //     y = -1;
        // }
        // if (!bool2) {
        //     y = -1;
        // }
            
        //     //last part 
        // if(matcher1.find()) {
        //         if(y == 1) {
        //             System.out.println(javab + " + " + x[1] + " = " + x[2]);
        //         }
        //         else if(y == -1) {
        //         System.out.println(-1);
        //         }
        // }
        // if(matcher2.find()) {
        //         if(y == 1) {
        //             System.out.println(x[1] + " + " + javab + " = " + x[2]);
        //         }
        //         else if(y == -1) {
        //             System.out.println(-1);
        //         }
        // }
            
        // if(matcher3.find()) {
        //         if(y == 1){
        //             System.out.println(x[1] + " + " + x[2] + " = " + javab);
        //         }
        //         else if(y == -1) {
        //             System.out.println(-1);
        //         }
        //}
    }
}










