#include "Client.h"

Client::Client(const std::string& name, const std::string& surname,
    const std::string& passport_data, const std::string& address)
    : name(name), surname(surname), passport_data(passport_data), address(address) {}

const std::string& Client::getName() const {
    return name;
}

const std::string& Client::getSurname() const {
    return surname;
}

const std::string& Client::getPassportData() const {
    return passport_data;
}

const std::string& Client::getAddress() const {
    return address;
}

void Client::setPassportData(const std::string& passport_data) {
    this->passport_data = passport_data;
}

void Client::setAddress(const std::string& address) {
    this->address = address;
}
