#include "Transaction.h"
#include <sstream>
#include <iomanip>

Transaction::Transaction(Account* fromAccount, Account* toAccount, double amount)
    : fromAccount(fromAccount), toAccount(toAccount), amount(amount), timestamp(time(0)), status(TransactionStatus::Completed) {
    // Generate a unique transaction ID (example)
    std::stringstream ss;
    ss << std::time(0) << "-" << fromAccount->getAccountId() << "-" << toAccount->getAccountId();
    transactionId = ss.str();
}

std::string Transaction::getTransactionId() const {
    return transactionId;
}

Account* Transaction::getFromAccount() const {
    return fromAccount;
}

Account* Transaction::getToAccount() const {
    return toAccount;
}

double Transaction::getAmount() const {
    return amount;
}

std::time_t Transaction::getTimestamp() const {
    return timestamp;
}

TransactionStatus Transaction::getStatus() const {
    return status;
}

void Transaction::cancel() {
    status = TransactionStatus::Cancelled;
}