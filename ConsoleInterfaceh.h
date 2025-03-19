#ifndef CONSOLEINTERFACE_H
#define CONSOLEINTERFACE_H

#include <string>
#include "Bank.h"
#include "CentralBank.h"

class ConsoleInterface {
public:
    ConsoleInterface(CentralBank* centralBank);
    void run();

private:
    CentralBank* centralBank;
    void displayMainMenu();
    void handleBankOperations(Bank& bank);
    // Добавьте другие вспомогательные методы для обработки пользовательского ввода
};

#endif
