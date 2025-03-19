#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <ctime>

// Forward declaration
class Client;

enum class AccountType {
    Debit,
    Deposit,
    Credit
};

class Account {
public:
    virtual ~Account() = default; // Важно для полиморфизма
    virtual void deposit(double amount) = 0;
    virtual bool withdraw(double amount) = 0;
    virtual double getBalance() const = 0;
    virtual std::string getAccountId() const = 0;
    virtual Client* getClient() const = 0;
    virtual void applyInterest() = 0;
    virtual void applyFee() = 0;
    virtual void undoTransaction(double amount) = 0;

protected:
    Account(std::string account_id, Client* client, double balance);

    std::string account_id;
    double balance;
    Client* client;
    std::time_t creation_date;
};

#endif
