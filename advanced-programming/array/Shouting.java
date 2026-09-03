import java.util.*;
public class Shouting {
    public static void main(String [] args) {
        Scanner input = new Scanner(System.in);
        int n, m;
        n = input.nextInt(); 
        m = input.nextInt();

        int[][] matris = new int[n][m];

        for(int i = 0 ; i < n ; i++) {
            for(int j = 0 ; j < m ; j++) {
                matris[i][j] = input.nextInt();
                
            }
        }
        // for(int i = 0 ; i < n ; i++) {
        //     for(int j = 0 ; j < m ; j++) {
        //         System.out.println(matris[i][j]);
                
        //     }
        // }
        int width = input.nextInt(); //x
        int height = input.nextInt(); //y
        String word;
        String help1 = input.nextLine();
        int number = 0;
        while(input.hasNext()) {
           
           word = input.nextLine();
           int length = word.length();
           char ch;
           int sound = 0;
           for(int k = 0 ; k < length ; k++) {
            ch = word.charAt(k);
            if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y') {
                sound++;
            }
           }
           number =  0;
           for(int x = 0 ; x < n ; x++) {
            for(int y = 0 ; y < m ; y++) {
                if((x - width <= sound) &&(x - width >= -sound) &&(y - height >= -sound) && (y - height <= sound)) {
                    number = number + matris[x][y];
                }
            }
           }
           System.out.println(number);
        }
    }
}