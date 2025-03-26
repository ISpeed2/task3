#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>
#include <memory>
#include "Client.h"
#include "Account.h"
#include "Transaction.h"
#include "Observer.h"
#include "Exceptions.h"
#include "TimeService.h"

class CentralBank;

class Bank : public Subject {
public:
    Bank(const std::string& name, const std::string& bank_id);
    ~Bank() override;

    void addClient(const Client& client);
    std::unique_ptr<Account> createAccount(Client& client, AccountType accountType, double initialBalance,
                                             double interestRate = 0.0, double creditLimit = 0.0, double fee = 0.0, long expirationTime = 0);
    void deposit(Account* account, double amount);
    bool withdraw(Account* account, double amount);
    bool transfer(Account* fromAccount, Account* toAccount, double amount);
    void calculateInterest();
    void applyFees();
    bool cancelTransaction(Transaction& transaction);

    const std::string& getName() const;
    const std::string& getBankId() const;
    std::vector<std::unique_ptr<Account>>& getAccounts();
    std::vector<Client>& getClients();

private:
    std::string name;
    std::string bank_id;
    std::vector<Client> clients;
    std::vector<std::unique_ptr<Account>> accounts;
    void notify() override;
    friend class CentralBank;
};

#endif
