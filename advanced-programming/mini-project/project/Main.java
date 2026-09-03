//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {

        Student s1 = new Student("Sara Shiri", 200512, 78);
        Student s2 = new Student("Ava Shiri", 229374, 96);
        Student s3 = new Student("Mohanna Vagozari", 33456, 34);
        Student s4 = new Student("Mitchel Cave", 669696, 23);
        Student s5 = new Student("Ali Komasi", 334455, 13);


        Teacher t1 = new Teacher("Mitra", "bolHasani", 998888);
        Course c1 = new Course("Math", t1, 3, "no exam");
        Course c3 = new Course("DarkMagic", t1, 15, "exam on 31 october"); //cause she looks like Bellatrix

        t1.addStudent(s1, c1);
        t1.addStudent(s1, c3);
        t1.addStudent(s2, c3);
        t1.addStudent(s3, c3);
        t1.addStudent(s5, c3);

        t1.addProject(c1, "inverse", 7);

        s1.printNumberOfVaheds();
        s1.printCourseAndGrade();



        Teacher t2 = new Teacher("Bob", "Ross", 2233455);
        Course c2 = new Course("Art", t2, 5, "On 13/32");
        t2.addStudent(s2, c2);
        s2.printNumberOfVaheds();
        s2.printCourseAndGrade();
        t2.addStudent(s3, c2);
        t2.addStudent(s4, c2);
        t2.addStudent(s5, c2);
        System.out.println(c2.getTedadStudents());


        s4.printCourseAndGrade();
        t2.removeStudent(s4, c2);
        s4.printCourseAndGrade();



        t1.nomredehi(s1, c3, (double)198.4);
        t1.nomredehi(s2, c3, (double)300);
        t1.nomredehi(s3, c3, (double)234);
        t1.nomredehi(s5, c3, (double)566);
        System.out.println(c3.nerdTarin());

        c3.printStudetns();

        s1.printCourseAndGrade();
        t1.removeStudent(s1, c3);
        s1.printCourseAndGrade();

    }
}