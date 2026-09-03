//
//import java.util.UUID;
//
//public class Transaction {
//    private UUID transactionIdentifier;
//    private String senderName;
//    private String receiverName;
//    private double transactionAmount;
//    private String transactionDescription;
//
//    public Transaction(String senderName, String receiverName, double transactionAmount, String transactionDescription) {
//        this.transactionIdentifier = UUID.randomUUID();
//        this.senderName = senderName;
//        this.receiverName = receiverName;
//        this.transactionAmount = transactionAmount;
//        this.transactionDescription = transactionDescription;
//    }
//
//    public UUID getTransactionIdentifier() {
//        return transactionIdentifier;
//    }
//
//    public String getSenderName() {
//        return senderName;
//    }
//
//    public String getReceiverName() {
//        return receiverName;
//    }
//
//    public double getTransactionAmount() {
//        return transactionAmount;
//    }
//
//    public String getTransactionDescription() {
//        return transactionDescription;
//    }
//}
//```
//
//        ### Updated `Transaction` Class Version 2
//        ```java

import java.time.LocalDateTime;

public class Transaction {
    private String transactionCode;
    private String sourceAccountName;
    private String destinationAccountName;
    private double transactionValue;
    private LocalDateTime transactionDateTime;

    public Transaction(String sourceAccountName, String destinationAccountName, double transactionValue, String transactionDescription) {
        this.transactionCode = generateTransactionCode();
        this.sourceAccountName = sourceAccountName;
        this.destinationAccountName = destinationAccountName;
        this.transactionValue = transactionValue;
        this.transactionDateTime = LocalDateTime.now();
    }

    private String generateTransactionCode() {
        // Different transaction code generation logic
        return "TX-" + Math.random();
    }

    public String getTransactionCode() {
        return transactionCode;
    }

    public String getSourceAccountName() {
        return sourceAccountName;
    }

    public String getDestinationAccountName() {
        return destinationAccountName;
    }

    public double getTransactionValue() {
        return transactionValue;
    }

    public LocalDateTime getTransactionDateTime() {
        return transactionDateTime;
    }

    public void setTransactionDateTime(LocalDateTime transactionDate) {
        this.transactionDateTime = transactionDate;
    }

    public void setTransactionCode(String transactionCode) {
        this.transactionCode =transactionCode;
    }
}