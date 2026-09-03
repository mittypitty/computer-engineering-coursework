import java.util.*;
public class Dade {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        String[] lines= new String[1500];
        int n = input.nextInt();
        int length = n;
        int number = 0;
        int mostcommon;
        int[] tool= new int[n];

        String string = input.next();
        //for the first line cause it has problems 
        for(int i = 0 ; i < length ; i++) {
            lines[i]= input.nextLine();
            number++;
            tool[i]= lines[i].length();
        }
        tool[0]++;

        // common number 
        int common = tool[0];
        int x = 1;
        int y = 0;
        for(int i = 0 ; i < tool.length ; i++) {
            y = 1;
            for(int j = i + 1 ; j < tool.length ; j++) {
                if(tool[i] == tool[j]) {
                    y++;
                }
                if(y > x) {
                    x = y;
                    common = tool[i];
                }

            }
        }
        mostcommon = common;

        int k = 0;
        while(k < n) {
            if((tool[k]) != mostcommon) {
                System.out.println(k);
            }
            k++;
        }
    }
}
