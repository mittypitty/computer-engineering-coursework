import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class User {
    private String name;
    private String username;
    private LocalDate birthdate;
    private final List<Video> videos = new ArrayList<>();
    public User(String name, String username, String birthdate) {
        this.name = name;
        this.username = username;
        this.birthdate = LocalDate.parse(birthdate);
    }
    public void setName(String name) {
        this.name = name;
    }
    public String getName() {
        return name;
    }
    public String getUsername() {
        return username;
    }
    public LocalDate getBirthdate() {
        return birthdate;
    }
    public List<Video> getVideos() {
        return videos;
    }
    public int age() {
        LocalDate currentDate = LocalDate.now();
        int userAge = currentDate.getYear() - birthdate.getYear();
        return userAge;
    }

    public void comment(Video videoName, String commentText) {
        Comment newComment = new Comment(commentText, this, videoName);
        videoName.submitComment(newComment);
    }

    public boolean watchVideo(Video newVideo) {
        if(age() >= newVideo.getAgeRestriction() || newVideo.getUploader() == this) {
            newVideo.views = newVideo.views + 1;
            return true;
        }
        else {
            return false;
        }
    }
}
