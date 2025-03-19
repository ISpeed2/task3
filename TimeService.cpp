#include "TimeService.h"

TimeService* TimeService::instance = nullptr;

TimeService* TimeService::getInstance() {
    if (!instance) {
        instance = new TimeService();
    }
    return instance;
}

TimeService::TimeService() : currentTime(time(0)) {}

TimeService::~TimeService() {
}

std::time_t TimeService::getCurrentTime() const {
    return currentTime;
}

void TimeService::advanceTime(long seconds) {
    currentTime += seconds;
}