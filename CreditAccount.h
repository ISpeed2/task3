#ifndef CREDITACCOUNT_H
#define CREDITACCOUNT_H

#include "Account.h"

class CreditAccount : public Account {
public:
    CreditAccount(std::string account_id, Client* client, double initialBalance, double creditLimit, double fee);

    void deposit(double amount) override;
    bool withdraw(double amount) override;
    double getBalance() const override;
    std::string getAccountId() const override;
    Client* getClient() const override;
    void applyInterest() override;
    void applyFee() override;
    void undoTransaction(double amount) override;

private:
    double creditLimit;
    double fee;
};

#endif