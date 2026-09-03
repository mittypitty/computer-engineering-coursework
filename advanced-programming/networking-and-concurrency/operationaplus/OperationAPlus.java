import java.io.*;
import java.nio.Buffer;
import java.util.*;

public class OperationAPlus{
    public static void gradeChanger(String studentName, String courseName, String grade, String baseAddress) {
        // todo

        ArrayList<String> str = new ArrayList<>();

        String name = courseName + ".txt";
        String path = baseAddress + "/" + name;
        boolean isHere = false;


        try {
            FileReader fileReader = new FileReader(path);
            Scanner scanner = new Scanner(fileReader);

            while (scanner.hasNextLine()) {
                str.add(scanner.nextLine());
            }

        } catch (IOException e) {
            throw new RuntimeException(e.getMessage());
        }


        for (int i = 0; i < str.size(); i++) {
            //TYLER...F
            String[] stName = str.get(i).split("\\.\\.\\.");

            if (stName[0].equals(studentName)) {
                isHere = true;
                stName[1] = grade;
                str.set(i, String.join("...", stName));
                break;
            }
        }

        if (isHere) {
            FileWriter fileWriter;
            try {
                fileWriter = new FileWriter(path);
            } catch (IOException e) {
                throw new RuntimeException(e.getMessage());
            }
            try {

                for (int i = 0; i < str.size(); i++) {
                    int size = str.size();
                    fileWriter.write(str.get(i));
                    if (i < size - 1) {
                        fileWriter.write("\n");
                    }
                }
                fileWriter.flush();
            } catch (IOException e) {
                throw new RuntimeException(e.getMessage());
            }
//           finally {
//                try {
//                    fileWriter.close();
//                } catch (IOException e) {
//                    throw new RuntimeException(e);
//                }
//            }
//        }

//        if(isHere) {
//            System.out.println(str);

        }
    }
    public static void main(String[] args) {
        OperationAPlus.gradeChanger("SARA","CA","D","C:\\Users\\USER\\Desktop\\initial (6)");

    }
}

