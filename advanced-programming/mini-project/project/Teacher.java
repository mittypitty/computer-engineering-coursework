import java.util.ArrayList;

public class Teacher {
    private String name;
    private String familyName;
    private int ostadCodeMelli;
    private int tedadDorus;
    public ArrayList<Course> courses = new ArrayList<>();


    public Teacher(String name, String familyName, int ostadCodeMelli) {
        this.name = name;
        this.familyName = familyName;
        this.ostadCodeMelli = ostadCodeMelli;
        tedadDorus =0;
        this.courses = new ArrayList<>();
    }

    public void addStudent(Student s,Course c){
            c.students.add(s);
            int temp = c.getTedadStudents();
            c.setTedadStudents(temp+1);
            s.tedadVahed += c.getVahed();
            s.tedadDorus += 1;
            s.studentList.put(c.getName(),(double)0);
    }

    public void removeStudent(Student s,Course c){
            c.students.remove(s);
            int temp = c.getTedadStudents();
            c.setTedadStudents(temp-1);
            s.studentList.remove(c.getName());
            s.tedadVahed -= c.getVahed();
            s.tedadDorus -= 1;
    }

    public void addProject(Course c, String title, int deadline){
        Assignment a = new Assignment(title,deadline,c);
        c.tamarin.add(a);
        int temp = c.getTedadStudents();
        c.setTedadTamarin(temp+1);
    }

    public void removeProject(Course c,Assignment a){
        c.tamarin.remove(a);
        int temp = c.getTedadStudents();
        c.setTedadTamarin(temp-1);
    }

    public void nomredehi(Student s,Course c ,double g){
            double temp = s.studentList.get(c.getName());
            s.studentList.put(c.getName(),g);

    }
}
