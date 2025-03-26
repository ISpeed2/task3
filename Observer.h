#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

class Subject; // Forward declaration

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(Subject* changedSubject) = 0;
};

class Subject {
public:
    virtual ~Subject() = default;

    void attach(Observer* observer);
    void detach(Observer* observer);
protected:
    void notify();

private:
    std::vector<Observer*> observers;
};

#endif
