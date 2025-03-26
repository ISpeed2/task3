#include "DepositAccount.h"
#include "Exceptions.h"
#include "TimeService.h"

DepositAccount::DepositAccount(std::string account_id, Client* client, double initialBalance, long expirationDate)
    : Account(account_id, client, initialBalance), expirationDate(expirationDate) {}

void DepositAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    } else {
        throw std::invalid_argument("Deposit amount must be positive.");
    }
}

bool DepositAccount::withdraw(double amount) {
    if (TimeService::getInstance()->getCurrentTime() > expirationDate) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            return true;
        } else {
            throw InsufficientFundsException("Insufficient funds for withdrawal.");
            return false;
        }
    } else {
        throw TransactionFailedException("Cannot withdraw before expiration date.");
        return false;
    }
}

double DepositAccount::getBalance() const {
    return balance;
}

std::string DepositAccount::getAccountId() const {
    return account_id;
}

Client* DepositAccount::getClient() const {
    return client;
}

void DepositAccount::applyInterest() {
    // Логика начисления процентов (зависит от банка)
}

void DepositAccount::applyFee() {
    // No fees for deposit accounts
}

void DepositAccount::undoTransaction(double amount) {
    balance += amount;
}
