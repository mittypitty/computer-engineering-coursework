import java.util.Arrays;
import java.util.Deque;
import java.util.LinkedList;
import java.util.*;

public class Bakery {


    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);

        int number = input.nextInt();
        input.nextLine();

        String peopleOrder = input.nextLine();
        String finalOrder = BakeryOrder(number, peopleOrder);

        System.out.println(finalOrder);
        //5
        //q-a-b-c-d
        //q-d-c-a-b
    }

    public static String BakeryOrder(int number, String str) {

        String[] splitedString = str.split("-");
        Deque<String> listOfPeople = new LinkedList<>(Arrays.asList(splitedString));
        StringBuilder sortingList = new StringBuilder();

        while (!listOfPeople.isEmpty()) {

            sortingList.append(listOfPeople.pollFirst()).append("-");


            if (listOfPeople.size() >= 2) {
                sortingList.append(listOfPeople.pollLast()).append("-");
                sortingList.append(listOfPeople.pollLast()).append("-");
            }

            else if (!listOfPeople.isEmpty()) {
                sortingList.append(listOfPeople.pollLast()).append("-");
            }
        }

        String finalOrder =  sortingList.substring(0, sortingList.length() - 1);
        return finalOrder;
    }
}
