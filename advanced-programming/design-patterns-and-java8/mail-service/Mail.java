public class Mail {
    private final User sender;
    private final User receiver;
    private final String content;
    private boolean read = false;
    
    public Mail(User sender, User receiver, String content) {
        this.sender = sender;
        this.receiver = receiver;
        this.content = content;
    }

    public boolean isRead() {
        return read;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null) {
            return false;
        }
        if (getClass() != o.getClass()) {
            return false;
        }

        Mail email = (Mail) o;
        return sender.equals(email.sender) && receiver.equals(email.receiver) && content.equals(email.content);
    }
    
    @Override
    public String toString() {
        return "sender=" + sender.getName() + ", receiver=" + receiver.getName() + ", content=" + content;
    }


    public void setRead(boolean read) {
        this.read = read;
    }

    public User getSender() {
        return sender;
    }

    public User getReceiver() {
        return receiver;
    }

    public String getContent() {
        return content;
    }

}
