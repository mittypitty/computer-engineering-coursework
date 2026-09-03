import java.util.*;

public class XSS {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int number = 0;
        int running = 0;
        String[] id = new String[20];
        String[] ramz = new String[20];

        while (running == 0) {
            String voroodi = input.nextLine();
            if (voroodi.equals("signup")) {
                String namkarbari = input.nextLine();

                // Check for XSS
                if (containsScript(namkarbari)) {
                    System.out.println("XSS Attack!");
                    continue; // Continue prompting for input
                }

                // Check if username already exists
                boolean usrExists = false;
                for (int i = 0; i < number; i++) {
                    if (namkarbari.equals(id[i])) {
                        usrExists = true;
                        System.out.println("Username Exists!");
                        break;
                    }
                }

                if (usrExists) {
                    continue; // Continue prompting for input
                }

                String password = input.nextLine();

                // Check for XSS
                if (containsScript(password)) {
                    System.out.println("XSS Attack!");
                    continue; // Continue prompting for input
                }

                // Check password validity
                if (isValidPassword(password)) {
                    id[number] = namkarbari;
                    ramz[number] = password;
                    System.out.println("SignUp Successful!");
                    number++;
                } else {
                    System.out.println("Password Not Valid!");
                }
            } else if (voroodi.equals("login")) {
                String loguser = input.nextLine();

                // Check for XSS
                if (containsScript(loguser)) {
                    System.out.println("XSS Attack!");
                    continue; // Continue prompting for input
                }
                if (number == 0) {
                    System.out.println("Invalid Username or Password!");
                    continue; // Continue prompting for input
                }

                boolean validCredentials = false;

                for (int i = 0; i < number; i++) {
                    if (loguser.equals(id[i])) {
                        validCredentials = true;
                        String loginPassword = input.nextLine();

                        // Check for XSS
                        if (containsScript(loginPassword)) {
                            System.out.println("XSS Attack!");
                            continue; // Continue prompting for input
                        }

                        if (loginPassword.equals(ramz[i])) {
                            System.out.println("Login Successful!");
                        } else {
                            System.out.println("Invalid Username or Password!");
                        }
                        break;
                    }
                }
                if (!validCredentials) {
                    System.out.println("Invalid Username or Password!");
                }
            } else if (voroodi.equals("exit")) {
                running = 1;
            }
        }
    }

    // Function to check for <script> tag in input
    private static boolean containsScript(String input) {
        boolean bool = false;
        int len = input.length()-1;
        if(input.charAt(0)!= '<' || input.charAt(len) != '>'){
            return false;
        }
        if(input.toLowerCase().contains("script")){
            bool = true;
        }
        else {
            return false;
        }
        int count =0;
        for(int i = 0 ; i < input.length() - 1 ; i++){
            if(input.toLowerCase().charAt(i) == 's' || input.toLowerCase().charAt(i) == 'c' || input.toLowerCase().charAt(i) == 'r' || input.toLowerCase().charAt(i) == 'i' || input.toLowerCase().charAt(i) == 'p' || input.toLowerCase().charAt(i) == 't'){
                count ++;
            }
        }
        if(count>6){
            return false;
        }
        for(int i = 0 ; i < input.length() - 1 ; i++) {
            if(input.toLowerCase().charAt(i) == 's' || input.toLowerCase().charAt(i) == 'c' || input.toLowerCase().charAt(i) == 'r' || input.toLowerCase().charAt(i) == 'i' || input.toLowerCase().charAt(i) == 'p' || input.toLowerCase().charAt(i) == 't' || input.toLowerCase().charAt(i) == ' ' || input.toLowerCase().charAt(i) == '<' || input.toLowerCase().charAt(i) == '>' || input.toLowerCase().charAt(i) == '/') {
                bool = true;
            }
            else {
                bool = false;
            }
        }
        return bool;
    }

    // Function to validate password
    private static boolean isValidPassword(String password) {
        // Add your password validation logic here
        return !password.contains("Script") && password.length() >= 8;
    }
}
