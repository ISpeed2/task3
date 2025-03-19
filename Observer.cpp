#include "Observer.h"

void Subject::attach(Observer* observer) {
    observers.push_back(observer);
}

void Subject::detach(Observer* observer) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            return;
        }
    }
}

void Subject::notify() {
    for (Observer* observer : observers) {
        observer->update(this);
    }
}
