#ifndef DEPOSITACCOUNT_H
#define DEPOSITACCOUNT_H

#include "Account.h"
#include <ctime>

class DepositAccount : public Account {
public:
    DepositAccount(std::string account_id, Client* client, double initialBalance, long expirationDate);

    void deposit(double amount) override;
    bool withdraw(double amount) override;
    double getBalance() const override;
    std::string getAccountId() const override;
    Client* getClient() const override;
    void applyInterest() override;
    void applyFee() override;
    void undoTransaction(double amount) override;

private:
    std::time_t expirationDate;
};

#endif
