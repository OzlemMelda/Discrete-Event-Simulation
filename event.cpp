
#include "event.h"

Event::Event(int hckrId, char event, float time) : hackerId(hckrId), event(event), time(time) {}
Event::Event(const Event& copyEvent) {
    this->hackerId = copyEvent.hackerId;
    this->serviceId = copyEvent.serviceId;
    this->event = copyEvent.event;
    this->time = copyEvent.time;
}
Event& Event::operator=(const Event& copyEvent) {
    this->hackerId = copyEvent.hackerId;
    this->serviceId = copyEvent.serviceId;
    this->event = copyEvent.event;
    this->time = copyEvent.time;
    return *this;
}
Event::Event(int hckrId, char event, float time, int srvcId) : hackerId(hckrId), event(event), time(time), serviceId(srvcId) {}
Event::~Event() {}

bool Event::operator<(const Event& rhs) const {
    return time > rhs.time;
}

bool Event::operator>(const Event& rhs) const {
    return rhs.time > this->time;
}

bool Event::operator<=(const Event& rhs) const {
    return !(rhs.time > this->time);
}

bool Event::operator>=(const Event& rhs) const {
    return !(this->time > rhs.time);
}

bool Event::operator==(const Event& rhs) const {
    return event == rhs.event &&
        hackerId == rhs.hackerId;
}

bool Event::operator!=(const Event& rhs) const {
    return !(event == rhs.event &&
        hackerId == rhs.hackerId);
}

char Event::getEvent() const {
    return event;
}

float Event::getTime() const {
    return time;
}

int Event::getHackerId() const {
    return hackerId;
}