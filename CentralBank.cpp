#include "CentralBank.h"
#include <iostream>

CentralBank* CentralBank::instance = nullptr;

CentralBank* CentralBank::getInstance() {
    if (!instance) {
        instance = new CentralBank();
    }
    return instance;
}

CentralBank::CentralBank() {}

CentralBank::~CentralBank() {
    for (Bank* bank : banks) {
        delete bank; // Удаляем выделенную память
    }
    banks.clear();
}

void CentralBank::addBank(Bank& bank) {
    banks.push_back(&bank);
    bank.attach(this); // Подписываем CentralBank на обновления от Bank
}

void CentralBank::removeBank(Bank& bank) {
    // Удаляем банк из вектора
    for (auto it = banks.begin(); it != banks.end(); ++it) {
        if (*it == &bank) {
            bank.detach(this); // Отписываем CentralBank от обновлений Bank
            banks.erase(it);
            return;
        }
    }
}

bool CentralBank::transferBetweenBanks(Account* fromAccount, Account* toAccount, double amount) {
    //  Находим банки, которым принадлежат счета.
    Bank* fromBank = nullptr;
    Bank* toBank = nullptr;

    for (Bank* bank : banks) {
        for (auto& account : bank->getAccounts()) {
            if (account.get() == fromAccount) {
                fromBank = bank;
            }
            if (account.get() == toAccount) {
                toBank = bank;
            }
        }
    }

    if (!fromBank || !toBank) {
        std::cerr << "One or both accounts not found in registered banks." << std::endl;
        return false;
    }

    //  Проверяем, достаточно ли средств и выполняем перевод.
    if (fromBank->withdraw(fromAccount, amount)) {
        toBank->deposit(toAccount, amount);
        return true;
    }
    else {
        std::cerr << "Insufficient funds in the source account." << std::endl;
        return false;
    }
}

void CentralBank::update(Subject* changedSubject) {
    if (Bank* bank = dynamic_cast<Bank*>(changedSubject)) {
        std::cout << "Central Bank received update from bank: " << bank->getName() << std::endl;
        // Дополнительная логика обработки изменений в банке
    }
}