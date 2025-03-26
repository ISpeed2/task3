#ifndef COMMAND_H
#define COMMAND_H

// Forward declaration
class Transaction;

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class CancelTransactionCommand : public Command {
public:
    CancelTransactionCommand(Transaction* transaction);
    void execute() override;
    void undo() override;

private:
    Transaction* transaction;
};

#endif
