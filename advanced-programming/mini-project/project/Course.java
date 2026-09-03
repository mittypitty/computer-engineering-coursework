import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Date;

public class Course {
    private String courseName;
    private Teacher ostad;
    private int vahed;
    public ArrayList<Student> students = new ArrayList<>();
    private int tedadStudents;
    private boolean activity;
    public ArrayList<Assignment> tamarin = new ArrayList<>();
    private int tedadTamarin;
    private String emtehan;


    public Course(String courseName, Teacher ostad, int vahed ,String emtehan) {
        this.courseName = courseName;
        this.ostad = ostad;
        this.vahed = vahed;
        this.emtehan = emtehan;
        this.students = new ArrayList<>();
        this.tamarin = new ArrayList<>();
        this.activity = true;
        this.tedadStudents =0;
        this.tedadTamarin =0;
        ostad.courses.add(this);
    }

    public void printStudetns(){
        for(Student s : students) {
            System.out.println(s.getNAme());
        }
    }

    public void studentAdder(Student s){
        students.add(s);
        tedadStudents ++;
        s.tedadDorus ++;
        s.tedadVahed += vahed;
        s.studentList.put(courseName , (double) 0);
    }

    public void studentRemover(Student s){
        students.remove(s);
        tedadStudents --;
        s.tedadDorus --;
        s.tedadVahed -= vahed;
        s.studentList.remove(this.courseName);
    }

    public String nerdTarin(){
        double best = 0;
        Student s2 = null;
        String name = "";
        for(Student s : students){
            if(s.studentList.get(this.courseName) >= best){
                best = s.studentList.get(this.courseName);
                s2 = s;
                name = s2.getNAme();
            }
        }
        return name;
    }

    public int getTedadStudents() {
        return tedadStudents;
    }

    public void setTedadStudents(int tedadStudents) {
        this.tedadStudents = tedadStudents;
    }

    public int getVahed() {
        return vahed;
    }
    public String getName() {
        return courseName;
    }

    public int getTedadTamarin() {
        return tedadTamarin;
    }

    public void setTedadTamarin(int tedadTamarin) {
        this.tedadTamarin = tedadTamarin;
    }
}
