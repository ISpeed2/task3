#include "ConsoleInterface.h"
#include <iostream>
#include <limits> // Для numeric_limits

ConsoleInterface::ConsoleInterface(CentralBank* centralBank) : centralBank(centralBank) {}

void ConsoleInterface::run() {
    while (true) {
        displayMainMenu();
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Проверка на корректность ввода
        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем остаток строки
            continue;
        }

        switch (choice) {
            case 1: {
                // Select a bank
                if (centralBank->banks.empty()) {
                    std::cout << "No banks registered yet." << std::endl;
                    break;
                }
                std::cout << "Available banks:" << std::endl;
                for (size_t i = 0; i < centralBank->banks.size(); ++i) {
                    std::cout << i + 1 << ". " << centralBank->banks[i]->getName() << std::endl;
                }
                int bankChoice;
                std::cout << "Enter the number of the bank: ";
                std::cin >> bankChoice;

                 // Проверка на корректность ввода
                if (std::cin.fail()) {
                    std::cout << "Invalid input. Please enter a number." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем остаток строки
                    break;
                }

                if (bankChoice > 0 && bankChoice <= centralBank->banks.size()) {
                    handleBankOperations(*centralBank->banks[bankChoice - 1]);
                } else {
                    std::cout << "Invalid bank choice." << std::endl;
                }
                break;
            }
            case 2:
                std::cout << "Exiting..." << std::endl;
                return;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }
}

void ConsoleInterface::displayMainMenu() {
    std::cout << "\n=== Banking System ===" << std::endl;
    std::cout << "1. Select Bank" << std::endl;
    std::cout << "2. Exit" << std::endl;
}

void ConsoleInterface::handleBankOperations(Bank& bank) {
    while (true) {
        std::cout << "\n=== " << bank.getName() << " Operations ===" << std::endl;
        std::cout << "1. Add Client" << std::endl;
        std::cout << "2. Create Account" << std::endl;
        std::cout << "3. Deposit" << std::endl;
        std::cout << "4. Withdraw" << std::endl;
        std::cout << "5. Transfer" << std::endl;
        std::cout << "6. Calculate Interest" << std::endl;
        std::cout << "7. Apply Fees" << std::endl;
        std::cout << "8. Back to Main Menu" << std::endl;

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

         // Проверка на корректность ввода
        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем остаток строки
            continue;
        }

        switch (choice) {
            case 1: {
                // Get client information from the user
                std::string name, surname, passport, address;
                std::cout << "Enter client name: ";
                std::cin >> name;
                std::cout << "Enter client surname: ";
                std::cin >> surname;
                std::cout << "Enter passport: ";
                std::cin >> passport;
                std::cout << "Enter address: ";
                // Использовать getline для чтения адреса с пробелами
                std::cin.ignore(); // Очистить символ новой строки после предыдущего cin
                std::getline(std::cin, address);

                // Create a new Client object
                Client newClient(name, surname, passport, address);

                // Add the client to the bank
                bank.addClient(newClient);

                std::cout << "Client added successfully." << std::endl;
                break;
            }

            case 2: {
                // Select a client
                if (bank.getClients().empty()) {
                    std::cout << "No clients registered yet." << std::endl;
                    break;
                }
                std::cout << "Available clients:" << std::endl;
                for (size_t i = 0; i < bank.getClients().size(); ++i) {
                    std::cout << i + 1 << ". " << bank.getClients()[i].getName() << " " << bank.getClients()[i].getSurname() << std::endl;
                }
                int clientChoice;
                std::cout << "Enter the number of the client: ";
                std::cin >> clientChoice;

                 // Проверка на корректность ввода
                if (std::cin.fail()) {
                    std::cout << "Invalid input. Please enter a number." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем остаток строки
                    break;
                }

                if (clientChoice > 0 && clientChoice <= bank.getClients().size()) {
                    // Select an account type
                    std::cout << "Select account type:" << std::endl;
                    std::cout << "1. Debit" << std::endl;
                    std::cout << "2. Deposit" << std::endl;
                    std::cout << "3. Credit" << std::endl;
                    int accountTypeChoice;
                    std::cout << "Enter your choice: ";
                    std::cin >> accountTypeChoice;

                     // Проверка на корректность ввода
                    if (std::cin.fail()) {
                        std::cout << "Invalid input. Please enter a number." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем остаток строки
                        break;
                    }

                    AccountType accountType;
                    switch (accountTypeChoice) {
                        case 1:
                            accountType = AccountType::Debit;
                            break;
                        case 2:
                            accountType = AccountType::Deposit;
                            break;
                        case 3:
                            accountType = AccountType::Credit;
                            break;
                        default:
                            std::cout << "Invalid account type choice." << std::endl;
                            break;
                    }

                     double initialBalance;
                     std::cout << "Enter initial balance: ";
                     std::cin >> initialBalance;

                      // Проверка на корректность ввода
                    if (std::cin.fail()) {
                        std::cout << "Invalid input. Please enter a number." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем остаток строки
                        break;
                    }
                     std::unique_ptr<Account> newAccount = bank.createAccount(bank.getClients()[clientChoice - 1], accountType, initialBalance);
                     bank.getAccounts().push_back(std::move(newAccount));
                     std::cout << "Account created successfully." << std::endl;

                 }
                break;
            }
            case 3: {
                // Получаем номер счета от пользователя
                std::string accountNumber;
                std::cout << "Введите номер счета для внесения средств: ";
                std::cin >> accountNumber;

                // Находим счет в банке
                Account* accountToDeposit = nullptr;
                for (auto& acc : bank.getAccounts()) {
                    if (acc->getAccountId() == accountNumber) {
                        accountToDeposit = acc.get(); // Получаем raw pointer
                        break;
                    }
                }

                if (accountToDeposit == nullptr) {
                    std::cout << "Счет с номером " << accountNumber << " не найден." << std::endl;
                    break;
                }

                // Получаем сумму для внесения
                double depositAmount;
                std::cout << "Введите сумму для внесения: ";
                std::cin >> depositAmount;

                 // Проверка на корректность ввода
                if (std::cin.fail()) {
                    std::cout << "Invalid input. Please enter a number." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем остаток строки
                    break;
                }

                // Вносим деньги на счет
                try {
                    bank.deposit(accountToDeposit, depositAmount);
                    std::cout << "Успешно внесено " << depositAmount << " на счет " << accountNumber << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка при внесении средств: " << e.what() << std::endl;
                }
                break;
            }
            case 4:
                std::cout << "Снятие средств находится в разработке. Пожалуйста, попробуйте позже." << std::endl;
                break;
            case 5:
                std::cout << "Перевод средств находится в разработке. Пожалуйста, попробуйте позже." << std::endl;
                break;
            case 6:
                std::cout << "Расчет процентов находится в разработке. Пожалуйста, попробуйте позже." << std::endl;
                break;
            case 7:
                std::cout << "Списание комиссий находится в разработке. Пожалуйста, попробуйте позже." << std::endl;
                break;
            case 8:
                return; // Back to Main Menu
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }
}
