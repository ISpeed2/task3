#ifndef DEBITACCOUNT_H
#define DEBITACCOUNT_H

#include "Account.h"

class DebitAccount : public Account {
public:
    DebitAccount(std::string account_id, Client* client, double initialBalance, double interestRate);

    void deposit(double amount) override;
    bool withdraw(double amount) override;
    double getBalance() const override;
    std::string getAccountId() const override;
    Client* getClient() const override;
    void applyInterest() override;
    void applyFee() override;
    void undoTransaction(double amount) override;

private:
    double interestRate;
};

#endif
