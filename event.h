#include <vector>
#include <string>
#include <ostream>
#include <iostream>

using namespace std;

#ifndef EVENT_H
#define EVENT_H


class Event {
    /* chars represent events type
        a:entry to system
        c:exit from sticker
        q:exit from system
       */
    char event;
    //time of the event
    float time;
    //the hacker who is doing this event
    int hackerId;

public:
    //the service who is doing this event(if it is entry service is -1)
    int serviceId = -1;

    Event();
    Event(int hckrId, char event, float time);
    Event(int hckrId, char event, float time, int srvcId);
    Event(const Event& copyEvent);
    Event& operator=(const Event& copyEvent);

    char getEvent() const;
    float getTime() const;
    int getHackerId() const;
    virtual ~Event();

    bool operator<(const Event& rhs) const;
    bool operator>(const Event& rhs) const;
    bool operator==(const Event& rhs) const;
    bool operator!=(const Event& rhs) const;
    bool operator<=(const Event& rhs) const;
    bool operator>=(const Event& rhs) const;

};

#endif //EVENT_H