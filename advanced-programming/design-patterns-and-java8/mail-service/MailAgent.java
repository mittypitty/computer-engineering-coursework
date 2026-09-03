public class MailAgent {
    private final User user;
    
    private MailAgent(User user) {
        this.user = user;
    }

    public boolean sendMail(String message, User receiver) {
        Mail email = new Mail(user, receiver, message);

        if(MailService.getObject().addMail(email)) {
            return true;
        }
        return false;
    }

    public String receiveMail() {
        String emails = "";
        int enter = 0;

        for(Mail email : MailService.getObject().getMails(user)) {
             enter++;
             emails += "sender=" + email.getSender().getName() + ", receiver=" + email.getReceiver().getName() + ", content=" + email.getContent();

             if(enter < MailService.getObject().getMails(user).size()) {
                 emails += "\n";
             }
        }
        return emails;
    }

    public static MailAgent createAgent(User user) {
        if(MailService.getObject().checkUser(user)) {

            MailAgent mAgent = new MailAgent(user);
            return mAgent;
        }
        return null;
    }

}
