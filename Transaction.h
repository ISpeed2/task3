#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

// Forward declarations
class Account;

enum class TransactionStatus {
    Completed,
    Cancelled
};

class Transaction {
public:
    Transaction(Account* fromAccount, Account* toAccount, double amount);

    std::string getTransactionId() const;
    Account* getFromAccount() const;
    Account* getToAccount() const;
    double getAmount() const;
    std::time_t getTimestamp() const;
    TransactionStatus getStatus() const;
    void cancel();

private:
    std::string transactionId;
    Account* fromAccount;
    Account* toAccount;
    double amount;
    std::time_t timestamp;
    TransactionStatus status;
};

#endif