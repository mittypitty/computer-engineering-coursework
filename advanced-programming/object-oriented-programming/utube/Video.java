import java.util.ArrayList;
import java.util.List;

public class Video {
    private String title;
    private User uploader;
    public int views = 0;
    private int ageRestriction;
    private final List<Comment> comments = new ArrayList<>();

    public Video(String title, User uploader, int ageRestriction) {
        this.title = title;
        this.uploader = uploader;
        this.ageRestriction = ageRestriction;
    }
    public String getTitle() {
        return title;
    }
    public User getUploader() {
        return uploader;
    }
    public int getAgeRestriction() {
        return ageRestriction;
    }
    public List<Comment> getComments() {
        return comments;
    } 
    public void setTitle(String title) {
        this.title = title;
    }
    public void submitComment(Comment comment) {
        comments.add(comment);
    }
}
