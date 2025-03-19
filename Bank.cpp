#include "Bank.h"
#include "DebitAccount.h"
#include "DepositAccount.h"
#include "CreditAccount.h"
#include <iostream>

Bank::Bank(const std::string& name, const std::string& bank_id) : name(name), bank_id(bank_id) {
}

Bank::~Bank() {
    // Явно удаляем каждый Account, чтобы убедиться, что деструкторы вызываются.
    accounts.clear();
}

void Bank::addClient(const Client& client) {
    clients.push_back(client);
}

std::unique_ptr<Account> Bank::createAccount(Client& client, AccountType accountType, double initialBalance) {
    std::string accountId = bank_id + "-" + std::to_string(accounts.size() + 1); // Unique ID

    switch (accountType) {
    case AccountType::Debit:
        return std::make_unique<DebitAccount>(accountId, &client, initialBalance, 0.05);
    case AccountType::Deposit:
        return std::make_unique<DepositAccount>(accountId, &client, initialBalance, TimeService::getInstance()->getCurrentTime() + (365 * 24 * 60 * 60)); // Пример expiration
    case AccountType::Credit:
        return std::make_unique<CreditAccount>(accountId, &client, initialBalance, 1000, 50); // Limit, fee
    default:
        throw InvalidAccountTypeException("Invalid account type");
    }
}

void Bank::deposit(Account* account, double amount) {
    if (amount > 0) {
        account->deposit(amount);
        notify(); // Observer pattern
    }
    else {
        throw std::invalid_argument("Deposit amount must be positive.");
    }
}

bool Bank::withdraw(Account* account, double amount) {
    try {
        if (account->withdraw(amount)) {
            notify(); // Observer pattern
            return true;
        }
        return false;
    }
    catch (const InsufficientFundsException& e) {
        std::cerr << "Withdrawal failed: " << e.what() << std::endl;
        return false;
    }
}

bool Bank::transfer(Account* fromAccount, Account* toAccount, double amount) {
    if (fromAccount->withdraw(amount)) { // Используем withdraw, а не напрямую balance -=
        try {
            toAccount->deposit(amount); // Используем deposit, а не напрямую balance +=
            notify(); // Observer pattern
            return true;
        }
        catch (...) {
            // Если deposit не удался, возвращаем деньги обратно на fromAccount
            fromAccount->deposit(amount);
            return false;
        }
    }
    return false;
}

void Bank::calculateInterest() {
    for (auto& account : accounts) {
        account->applyInterest();
    }
}

void Bank::applyFees() {
    for (auto& account : accounts) {
        account->applyFee();
    }
}

bool Bank::cancelTransaction(Transaction& transaction) {
    // Логика отмены транзакции (возврат средств и изменение статуса)
    //  Нужно убедиться, что у вас есть доступ к счетам, участвующим в транзакции.
    if (transaction.getStatus() == TransactionStatus::Completed) {
        Account* fromAccount = transaction.getFromAccount();
        Account* toAccount = transaction.getToAccount();
        double amount = transaction.getAmount();

        // Возвращаем деньги на счет отправителя (если он еще существует)
        if (fromAccount != nullptr) {
            fromAccount->undoTransaction(amount);
        }

        // Снимаем деньги со счета получателя (если он еще существует)
        if (toAccount != nullptr) {
            toAccount->withdraw(amount);
        }

        transaction.cancel();
        notify();
        return true;
    }
    else {
        return false;
    }
}

const std::string& Bank::getName() const {
    return name;
}

const std::string& Bank::getBankId() const {
    return bank_id;
}

std::vector<std::unique_ptr<Account>>& Bank::getAccounts() {
    return accounts;
}

std::vector<Client>& Bank::getClients() {
    return clients;
}

void Bank::notify() {
    Subject::notify(); // Вызов базовой реализации
}