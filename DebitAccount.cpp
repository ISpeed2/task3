#include "DebitAccount.h"
#include "Exceptions.h"

DebitAccount::DebitAccount(std::string account_id, Client* client, double initialBalance, double interestRate)
    : Account(account_id, client, initialBalance), interestRate(interestRate) {}

void DebitAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
    else {
        throw std::invalid_argument("Deposit amount must be positive.");
    }
}

bool DebitAccount::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    }
    else {
        throw InsufficientFundsException("Insufficient funds for withdrawal.");
        return false;
    }
}

double DebitAccount::getBalance() const {
    return balance;
}

std::string DebitAccount::getAccountId() const {
    return account_id;
}

Client* DebitAccount::getClient() const {
    return client;
}

void DebitAccount::applyInterest() {
    balance += balance * interestRate;
}

void DebitAccount::applyFee() {
    // No fees for debit accounts
}

void DebitAccount::undoTransaction(double amount) {
    balance += amount;
}