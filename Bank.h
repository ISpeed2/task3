#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>
#include <memory> // Для unique_ptr
#include "Client.h"
#include "Account.h"
#include "Transaction.h"
#include "Observer.h"
#include "Exceptions.h" // Для исключений
#include "TimeService.h" //  Для работы со временем

// Forward declaration
class CentralBank;

class Bank : public Subject {
public:
    Bank(const std::string& name, const std::string& bank_id);
    ~Bank() override;

    void addClient(const Client& client);
    std::unique_ptr<Account> createAccount(Client& client, AccountType accountType, double initialBalance);
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
    //std::unique_ptr<InterestRateStrategy> interest_rate_strategy; // Пример Strategy

    // Observer Pattern
    void notify() override;

    // Friend class для доступа к приватным членам (если нужно)
    friend class CentralBank;
};

#endif