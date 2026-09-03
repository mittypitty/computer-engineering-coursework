import java.util.Scanner;

public class Jarfa {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int number = scanner.nextInt();
        int[] array = new int[number];
        for (int i = 0; i < number; i++) {
            array[i] = scanner.nextInt();
        }
        if (number == 0) {
            System.out.println(0);
            return;
        }
        else if (number == 2) {
            System.out.println(2);
            return;
        }
        int minDepth = (int) Math.floor(Math.log(number + 1) / Math.log(2));
        System.out.println(minDepth);
    }
}

