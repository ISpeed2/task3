#ifndef CENTRALBANK_H
#define CENTRALBANK_H

#include <vector>
#include "Bank.h"
#include "Observer.h"

class CentralBank : public Observer {
public:
    static CentralBank* getInstance(); // Singleton

    void addBank(Bank& bank);
    void removeBank(Bank& bank);
    bool transferBetweenBanks(Account* fromAccount, Account* toAccount, double amount);

    void update(Subject* changedSubject) override; // Observer

private:
    CentralBank(); // Private constructor for Singleton
    ~CentralBank() override;

    std::vector<Bank*> banks;  //  Вектор указателей на Bank
    static CentralBank* instance;
};

#endif
