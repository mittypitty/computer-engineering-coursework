
public class AccountView {

	String accountInfo(Account account) {
		if (account == null) {
			return "No account found";
		}
		return "account with id " + account.getId() + " is held by " + account.getName() + " and has " + account.getBalance() + "$";
	}

	String transitionInfo(boolean success) {
		if(success) {
			return "Transition successful";
		}
		return "Transition failed";
	}
}