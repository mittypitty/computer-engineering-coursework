public class Account {
	String name;
	int id;
	int money;

	Account(String name, int id, int money) {
		this.name = name;
		this.id = id;
		this.money = money;
	}

	public String getName() {
		return name;
	}

	public int getBalance() {
		return money;
	}

	public int getId() {
		return id;
	}

	void deposit(int amount) {
		if(amount >= 0) {
			money += amount;
		}
	}

	boolean withdraw(int amount) {
		if(amount <= money && amount >= 0) {
			money -= amount;
			return true;
		}
		return false;
	}
}