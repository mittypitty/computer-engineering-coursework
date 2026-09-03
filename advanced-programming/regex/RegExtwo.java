import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.Scanner;

public class RegExtwo {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String email = input.nextLine();

        Pattern pattern1 = Pattern.compile(".*mindless.*@[aA]company[Aa]\\.(com|Com|cOm|coM|COm|CoM|cOM|COM|ir|IR|iR|Ir|net|Net|nEt|neT|NEt|NeT|nET|NET)");
        Pattern pattern2 = Pattern.compile(".*[\\d]{1,}.*@[aA]company[Aa]\\.(com|Com|cOm|coM|COm|CoM|cOM|COM|ir|IR|iR|Ir|net|Net|nEt|neT|NEt|NeT|nET|NET)");
        Pattern pattern3 = Pattern.compile(".{9,15}@[aA]company[Aa]\\.(com|Com|cOm|coM|COm|CoM|cOM|COM|ir|IR|iR|Ir|net|Net|nEt|neT|NEt|NeT|nET|NET)");

        Matcher matcher1 = pattern1.matcher(email);
        Matcher matcher2 = pattern2.matcher(email);
        Matcher matcher3 = pattern3.matcher(email);

        if (matcher1.find() && matcher2.find() && matcher3.find()) {
            System.out.println("ok");
        } else {
            System.out.println("invalid");
        }
    }
}
