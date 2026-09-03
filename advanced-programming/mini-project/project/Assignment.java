public class Assignment {
    private String title;
    private int deadline;
    private boolean active;


    public Assignment(String title, int deadline,Course course) {
        this.title = title;
        this.deadline = deadline;
        this.active = true;
        course.tamarin.add(this);
    }

    public void changeDeadline(int dl){
        this.deadline = dl;
    }
}
