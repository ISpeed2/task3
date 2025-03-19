#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class BankingException : public std::exception {
public:
    BankingException(const std::string& message) : message_(message) {}
    const char* what() const noexcept override { return message_.c_str(); }

protected:
    std::string message_;
};

class InsufficientFundsException : public BankingException {
public:
    InsufficientFundsException(const std::string& message) : BankingException(message) {}
};

class InvalidAccountTypeException : public BankingException {
public:
    InvalidAccountTypeException(const std::string& message) : BankingException(message) {}
};

class TransactionFailedException : public BankingException {
public:
    TransactionFailedException(const std::string& message) : BankingException(message) {}
};

#endif