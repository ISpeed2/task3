#include <iostream>
#include <memory>
#include "CentralBank.h"
#include "Bank.h"
#include "Client.h"
#include "Account.h"
#include "DebitAccount.h"
#include "CreditAccount.h"
#include "DepositAccount.h"
#include "Exceptions.h"
#include "ConsoleInterface.h"
#include "LoggerFactory.h"

int main() {
    // Создаем CentralBank (Singleton)
    CentralBank* centralBank = CentralBank::getInstance();

    // Создаем LoggerFactory
    LoggerFactory* loggerFactory = new ConsoleLoggerFactory();
    Logger* logger = loggerFactory->createLogger();

    // Создаем Bank
    Bank* bank = new Bank("MyBank", "MB123");
    centralBank->addBank(*bank);
    logger->log("Bank created: MyBank");

    // Создаем Client
    Client client("John", "Doe", "123456789", "123 Main St");
    bank->addClient(client);
    logger->log("Client created: John Doe");

    // Создаем DebitAccount
    std::unique_ptr<Account> debitAccount = bank->createAccount(client, AccountType::Debit, 1000.0, 0.05);
    if (debitAccount) {
        bank->getAccounts().push_back(std::move(debitAccount)); // Перемещаем владение в вектор accounts
        logger->log("Debit account created for John Doe");
    } else {
        std::cerr << "Failed to create debit account" << std::endl;
        return 1;
    }

    Account* acc = bank->getAccounts()[0].get();
    // Perform some operations
    bank->deposit(acc, 500.0);
    logger->log("Deposited 500 into debit account");

    try {
        bank->withdraw(acc, 200.0);
        logger->log("Withdrew 200 from debit account");
    } catch (const InsufficientFundsException& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        logger->log("Withdrawal failed (insufficient funds)");
    }

    bank->calculateInterest();
    logger->log("Interest calculated");

    // Создаем ConsoleInterface и запускаем его
    ConsoleInterface consoleInterface(centralBank);
    consoleInterface.run();

    // Clean up memory
    delete logger;
    delete loggerFactory;
    centralBank->removeBank(*bank);  // Важно удалить банк из CentralBank перед удалением самого банка
    delete bank; // Важно: удаляем банк после удаления из CentralBank
    CentralBank::cleanup();  // Вызываем cleanup для Singleton

    return 0;
}
