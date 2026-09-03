import java.util.Scanner;

public class SortedLinkedList {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        if (n <= 0 || n > 100) {
            return;
        }
        SortedList mylist = new SortedList();
        for (int i = 0; i < n; i++) {
            int num = scanner.nextInt();
            if (num < -100 || num > 100) {
                return;
            }
            mylist.insert(num);
        }
        int x = scanner.nextInt();
        if (x < -100 || x > 100) {
            return;
        }
        mylist.insert(x);
        mylist.printList();
        scanner.close();
    }
}
class Node {
    int data;
    Node next;
    Node(int value) {
        this.data = value;
        this.next = null;
    }
}
class SortedList {
    private Node front;
    SortedList() {
        this.front = null;
    }
    void insert(int value) {
        Node newNode = new Node(value);
        if (front == null || value < front.data) {
            newNode.next = front;
            front = newNode;
            return;
        }
        Node current = front;
        Node prev = null;
        while (current != null && current.data <= value) {
            prev = current;
            current = current.next;
        }
        prev.next = newNode;
        newNode.next = current;
    }
    void printList() {
        Node current = front;
        while (current != null) {
            System.out.print(current.data);
            if (current.next != null) {
                System.out.print(" ");
            }
            current = current.next;
        }
        System.out.println();
    }
}

