#include "Account.h"

Account::Account(std::string account_id, Client* client, double balance) :
    account_id(account_id), balance(balance), client(client), creation_date(time(0)) {}