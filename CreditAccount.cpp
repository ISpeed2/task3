#include "CreditAccount.h"
#include "Exceptions.h"

CreditAccount::CreditAccount(std::string account_id, Client* client, double initialBalance, double creditLimit, double fee)
    : Account(account_id, client, initialBalance), creditLimit(creditLimit), fee(fee) {}

void CreditAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
    else {
        throw std::invalid_argument("Deposit amount must be positive.");
    }
}

bool CreditAccount::withdraw(double amount) {
    if (amount > 0 && (balance + creditLimit) >= amount) {
        balance -= amount;
        return true;
    }
    else {
        throw InsufficientFundsException("Exceeds credit limit.");
        return false;
    }
}

double CreditAccount::getBalance() const {
    return balance;
}

std::string CreditAccount::getAccountId() const {
    return account_id;
}

Client* CreditAccount::getClient() const {
    return client;
}

void CreditAccount::applyInterest() {
    // No interest on credit accounts
}

void CreditAccount::applyFee() {
    if (balance < 0) {
        balance -= fee;
    }
}

void CreditAccount::undoTransaction(double amount) {
    balance += amount;
}