import java.util.ArrayList;
import java.util.List;

public class MailService {
    private final List<Mail> mails = new ArrayList<>();
    private final List<User> registerUsers = new ArrayList<>();
    private static MailService inst;

    private MailService() {}

    public static MailService getObject() {
        if (inst == null) {
            inst = new MailService();
        }
        return inst;
    }

    public boolean checkUser(User user) {
        if(registerUsers.contains(user)) {
            return true;
        }
        return false;
    }

    public boolean addMail(Mail mail) {
        if((mails.contains(mail)) || (mail.getContent().length() > 255) || (mail.getSender().allowedEmails <= 0)) {

            return false;
        }
        mail.getSender().allowedEmails--;
        mails.add(mail);
        return true;
    }

    public List<Mail> getMails(User user) {
        List<Mail> receiveEmails = new ArrayList<>();

        for(Mail email : mails) {
            if (email.getReceiver() == user) {
                email.setRead(true);
                receiveEmails.add(email);
            }
        }
        return receiveEmails;
    }

    public List<Mail> getMails() {
        return mails;
    }

    public List<User> getRegisterUsers() {
        return registerUsers;
    }

}
