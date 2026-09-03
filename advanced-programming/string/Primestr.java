import java.lang.*;
import java.io.*;
import java.util.*;
public class Primestr {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int number;
        number = input.nextInt();
        input.nextLine();
        String alphabet;
        alphabet = input.nextLine();
        int mod;
        boolean isPrime = true;
        for(int i = 2 ; i <number ; i++) {
            mod = number % i;
            if(mod == 0) {
                isPrime = false;
                break;
            }
        }
        char ch;
        if(!isPrime) {
            String reverseStr = "";
            
            for(int j = 0 ; j < alphabet.length() ; j++) {
                ch = alphabet.charAt(j);
                reverseStr = ch + reverseStr;
            }
            System.out.println(reverseStr);
        }
        else {
            System.out.println(alphabet);
        }
    }
}