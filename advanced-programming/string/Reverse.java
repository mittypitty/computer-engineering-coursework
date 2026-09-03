import java.util.*;
import java.lang.*;
public class Reverse {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String firststr = input.nextLine();
        int first = 0, last = 0;
        String str = "";
        while(last < firststr.length()) {
            while((last < firststr.length()) && (Character.isLetter(firststr.charAt(last))) ) {
                last++;
            }
            String str2 = "";
            for(int i = last - 1; i >= first; i--) {
                str2 += firststr.charAt(i);
            }
            str += str2 + " ";
            System.out.print(str2 + " ");
            first =last;
            while((first < firststr.length()) && (!Character.isLetter(firststr.charAt(first))) ) {
                first++;
                last = first;
            }
        }
    }
}