#include <vector>
using namespace std;

#ifndef HACKER_H
#define HACKER_H

class Hacker {
    int id;
    float arrivalTime;
    float leavingTime = -1;
    vector<float>commitTimes;
    vector<int>commitLines;

public:
    float leaveStickerTime = 0;
    float enterStickerTime = 0;
    float turnAroundTime = 0;

    float enterStickerQueueTime = 0;
    float enterHoodieQueueTime = 0;
    float leaveHoodieQueueTime = 0;
    float leaveStickerQueueTime = 0;
    float waitingStickerQueueTime = 0;
    float waitingHoodieQueueTime = 0;
    float totalWaitingTime = 0;

    int giftCount = 0;

    Hacker();
    Hacker(int id, float arrivalTime, vector<float> commitTimes, vector<int> commitLines);
    Hacker(const Hacker& hacker);
    virtual ~Hacker();
    Hacker& operator=(const Hacker& hckr);

    float getArrivalTime() const;
    float getLeavingTime() const;
    int getCommitCount() const;
    vector<float> getCommitTimes() const;
    vector<int> getCommitLines() const;
    int getId() const;
    void setLeavingTime(float leavingTime);

    bool operator<(const Hacker& rhs) const;
    bool operator>(const Hacker& rhs) const;
    bool operator<=(const Hacker& rhs) const;
    bool operator>=(const Hacker& rhs) const;
    bool operator==(const Hacker& rhs) const;
};

#endif //HACKER_H