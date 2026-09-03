import java.util.*;
public class Tamrin1 {
    public static void main(String [] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int [] arr = new int[n];
        for(int i = 0 ; i < n ; i++) {
            int x = input.nextInt();
            arr[i] = x;
        }
        Bubble_Sort(arr, n);

    }

    public static void Bubble_Sort(int arr[], int n) {
        for (int i = 0 ; i < n - 1 ; i++) {
            for (int j = 0 ; j < n - i - 1 ; j++) {
                if (arr[j] < arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        h_index(arr, n);
    }
    
    public static void h_index(int arr[], int n) {
        int hIndex = 0;
            for (int i = 0 ; i < n ; i++) {
                if (arr[i] >= (i + 1)) {
                    hIndex = i + 1;
                }
                else {
                    break;
                }
            }
        System.out.println(hIndex);
    }
}
