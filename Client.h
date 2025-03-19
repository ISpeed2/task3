#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
public:
    Client(const std::string& name, const std::string& surname,
        const std::string& passport_data = "", const std::string& address = "");

    const std::string& getName() const;
    const std::string& getSurname() const;
    const std::string& getPassportData() const;
    const std::string& getAddress() const;

    void setPassportData(const std::string& passport_data);
    void setAddress(const std::string& address);

private:
    std::string name;
    std::string surname;
    std::string passport_data;
    std::string address;
    //std::string client_id;  ћожно добавить, если нужен уникальный ID
};

#endif