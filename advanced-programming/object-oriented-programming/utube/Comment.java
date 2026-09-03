import java.time.LocalDate;
import java.time.LocalDateTime;

public class Comment {
    private String text;
    private User author;
    private Video video;
    private LocalDateTime createdAt;
     
    public Comment(String text, User author, Video video) {
        this.text = text;
        this.author = author;
        this.video = video;
        this.createdAt = LocalDateTime.now();
    }
    public String getText() {
        return text;
    }
    public User getAuthor() {
        return author;
    }
    public Video getVideo() {
        return video;
    }
    public LocalDateTime getCreatedAt() {
        return createdAt;
    }
}
