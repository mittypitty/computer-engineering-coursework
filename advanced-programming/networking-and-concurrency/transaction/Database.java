import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Database {
    private static final String url = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String user = "root";
    private static final String password = "password";

    public void saveTransaction(Transaction transaction) {
        String query = "INSERT INTO transactions (transaction_code, source_account_name, destination_account_name, transaction_value, transaction_date) VALUES (?, ?, ?, ?, ?)";

        try (Connection con = DriverManager.getConnection(url, user, password);
             PreparedStatement pst = con.prepareStatement(query)) {

            pst.setString(1, transaction.getTransactionCode());
            pst.setString(2, transaction.getSourceAccountName());
            pst.setString(3, transaction.getDestinationAccountName());
            pst.setDouble(4, transaction.getTransactionValue());
            pst.setObject(5, transaction.getTransactionDateTime());

            pst.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public List<Transaction> getAllTransactions() {
        List<Transaction> transactions = new ArrayList<>();
        String query = "SELECT * FROM transactions";

        try (Connection con = DriverManager.getConnection(url, user, password);
             PreparedStatement pst = con.prepareStatement(query);
             ResultSet rs = pst.executeQuery()) {

            while (rs.next()) {
                Transaction transaction = new Transaction(
                        rs.getString("source_account_name"),
                        rs.getString("destination_account_name"),
                        rs.getDouble("transaction_value"),
                        rs.getString("transaction_description")
                );
                transaction.setTransactionCode(rs.getString("transaction_code"));
                transaction.setTransactionDateTime(rs.getObject("transaction_date", LocalDateTime.class));
                transactions.add(transaction);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return transactions;
    }

    public void deleteTransaction(String transactionCode) {
        String query = "DELETE FROM transactions WHERE transaction_code = ?";

        try (Connection con = DriverManager.getConnection(url, user, password);
             PreparedStatement pst = con.prepareStatement(query)) {

            pst.setString(1, transactionCode);
            pst.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}