import java.util.HashMap;
public class Student {
    private String studentName;
    private int studentCodeMelli;
    private int studentId;
    public int tedadDorus;
    public int tedadVahed;
    private int moadelKol;
    private int moadelTerm;
    public HashMap<String, Double> studentList = new HashMap<>();


    public Student(String studentName, int studentCodeMelli, int studentId) {
        this.studentName = studentName;
        this.studentCodeMelli = studentCodeMelli;
        this.studentId = studentId;
        moadelTerm = moadelKol = tedadDorus = tedadVahed = 0;
        HashMap<Course, Double> studentList = new HashMap<Course, Double>();
    }

    public void printNumberOfVaheds() {
        System.out.println(tedadVahed);
    }


    public void moadelgir() {
        int sum = 0;
        for (Double i : studentList.values()) {
            sum += i;
        }
        moadelTerm = moadelKol = sum / studentList.size();
        System.out.println(sum / studentList.size());
    }

    public void printCourseAndGrade() {
        System.out.println(studentList);
    }

    public String getNAme(){
        return studentName;
    }
}