#ifndef TIMESERVICE_H
#define TIMESERVICE_H

#include <ctime>

class TimeService {
public:
    static TimeService* getInstance();
    std::time_t getCurrentTime() const;
    void advanceTime(long seconds);

private:
    TimeService();
    ~TimeService();

    static TimeService* instance;
    std::time_t currentTime;
};

#endif