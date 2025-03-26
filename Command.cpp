#include "Command.h"
#include <iostream>

CancelTransactionCommand::CancelTransactionCommand(Transaction* transaction) : transaction(transaction) {}

void CancelTransactionCommand::execute() {
    // Логика отмены транзакции
    std::cout << "Executing: Cancelling transaction " << transaction->getTransactionId() << std::endl;
    transaction->cancel();
}

void CancelTransactionCommand::undo() {
    // Логика восстановления транзакции (если это необходимо)
    std::cout << "Undoing: Cancelling transaction " << transaction->getTransactionId() << std::endl;
    //transaction->setStatus(TransactionStatus::Completed);
}
