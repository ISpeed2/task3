#include "ConsoleInterface.h"
#include <iostream>

ConsoleInterface::ConsoleInterface(CentralBank* centralBank) : centralBank(centralBank) {}

void ConsoleInterface::run() {
    while (true) {
        displayMainMenu();
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

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

            if (bankChoice > 0 && bankChoice <= centralBank->banks.size()) {
                handleBankOperations(*centralBank->banks[bankChoice - 1]);
            }
            else {
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

        switch (choice) {
        case 1: {
            // Get client information from the user
            std::string name, surname, passport, address;
            std::cout << "Enter client name: ";
            std::cin >> name;
            std::cout << "Enter client surname: ";
            std::cin >> surname;
            std::cout << "Enter passport ";
            std::cin >> passport;
            std::cout << "Enter address: ";
            std::cin >> address;

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

            if (clientChoice > 0 && clientChoice <= bank.getClients().size()) {
                // Select an account type
                std::cout << "Select account type:" << std::endl;
                std::cout << "1. Debit" << std::endl;
                std::cout << "2. Deposit" << std::endl;
                std::cout << "3. Credit" << std::endl;
                int accountTypeChoice;
                std::cout << "Enter your choice: ";
                std::cin >> accountTypeChoice;

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
                std::unique_ptr<Account> newAccount = bank.createAccount(bank.getClients()[clientChoice - 1], accountType, initialBalance);
                bank.getAccounts().push_back(std::move(newAccount));
                std::cout << "Account created successfully." << std::endl;

            }
            break;
        }
        case 3:
            // Deposit logic
            break;
        case 4:
            // Withdraw logic
            break;
        case 5:
            // Transfer logic
            break;
        case 6:
            // Calculate Interest logic
            break;
        case 7:
            // Apply Fees logic
            break;
        case 8:
            return; // Back to Main Menu
        default:
            std::cout << "Invalid choice." << std::endl;
        }
    }
}
