
import java.util.ArrayList;
import java.util.List;

public class Bank {
	List<Account> accounts = new ArrayList<>();

	boolean openAccount(String name) {
		if (accounts.size() < 100) {
			accounts.add(new Account(name, accounts.size(), 0));
			return true;
		}

		return false;
	}

	boolean deposit(int id, int amount) {
		if(findAccount(id) == null) {
			return false;
		}
		else {
			Account acc = findAccount(id);
			acc.deposit(amount);
			return true;
		}
	}

	boolean withdraw(int id, int amount) {
		if (findAccount(id) == null) {
			return false;
		}
		Account acc = findAccount(id);
		return acc.withdraw(amount);
	}

	boolean transfer(int from, int to, int amount) {
		if((findAccount(from) == null) || (findAccount(to) == null) || (findAccount(from).getBalance() < amount)) {
			return false;
		}
		else {
			findAccount(from).withdraw(amount);
			findAccount(to).deposit(amount);
			return true;
		}
	}

	Account findAccount(int id){
		for (Account acc : accounts) {
			if(acc.getId() == id) {
				return acc;
			}
		}
		return null;
	}
}