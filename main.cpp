#include <iostream>
#include "Bank.h"
#include "Client.h"
#include "Account.h"
#include "CentralBank.h"
#include "ConsoleInterface.h"
#include "TimeService.h"
#include "LoggerFactory.h"

int main() {
    // Logger initialization
    ConsoleLoggerFactory loggerFactory;
    Logger* logger = loggerFactory.createLogger();

    // Central Bank Singleton
    CentralBank* centralBank = CentralBank::getInstance();
    logger->log("Central Bank instance created.");

    // Bank creation
    Bank* bank = new Bank("MyBank", "MB123");
    centralBank->addBank(*bank);
    logger->log("Bank created: MyBank");

    // Client creation
    Client client("John", "Doe", "Passport123", "123 Main St");
    bank->addClient(client);
    logger->log("Client added: John Doe");

    //ConsoleInterface interface(centralBank);
    //interface.run();

    std::unique_ptr<Account> debitAccount = bank->createAccount(client, AccountType::Debit, 1000.0);
    logger->log("Debit account created for John Doe");
    bank->deposit(debitAccount.get(), 500.0);
    logger->log("Deposited 500 into debit account");
    try {
        bank->withdraw(debitAccount.get
