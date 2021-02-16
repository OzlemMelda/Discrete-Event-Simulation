
#include <iostream>
#include "hacker.h"

Hacker::Hacker(int id, float arrivalTime, vector<float> commitTimes, vector<int> commitLines) : id(id), arrivalTime(arrivalTime), commitTimes(commitTimes), commitLines(commitLines) {
}

Hacker::Hacker(const Hacker& hacker) {
    this->id = hacker.id;
    this->arrivalTime = hacker.arrivalTime;
    this->leavingTime = hacker.leavingTime;
    this->leaveStickerTime = hacker.leaveStickerTime;
    this->waitingStickerQueueTime = hacker.waitingStickerQueueTime;
    this->waitingHoodieQueueTime = hacker.waitingHoodieQueueTime;
    this->enterStickerQueueTime = hacker.enterStickerQueueTime;
    this->enterHoodieQueueTime = hacker.enterHoodieQueueTime;
    this->leaveStickerQueueTime = hacker.leaveStickerQueueTime;
    this->leaveHoodieQueueTime = hacker.leaveHoodieQueueTime;
    this->totalWaitingTime = hacker.totalWaitingTime;
    this->enterStickerTime = hacker.enterStickerTime;
    this->turnAroundTime = hacker.turnAroundTime;
    
    for (int i = 0; i < hacker.commitTimes.size(); i++)
    {
        commitTimes.push_back(hacker.commitTimes[i]);
    }
    for (int i = 0; i < hacker.commitLines.size(); i++)
    {
        commitLines.push_back(hacker.commitLines[i]);
    }
}

Hacker::~Hacker() {
}

Hacker& Hacker::operator=(const Hacker& hacker) {
    this->id = hacker.id;
    this->arrivalTime = hacker.arrivalTime;
    this->leavingTime = hacker.leavingTime;
    this->leaveStickerTime = hacker.leaveStickerTime;
    this->waitingStickerQueueTime = hacker.waitingStickerQueueTime;
    this->waitingHoodieQueueTime = hacker.waitingHoodieQueueTime;
    this->enterStickerQueueTime = hacker.enterStickerQueueTime;
    this->enterHoodieQueueTime = hacker.enterHoodieQueueTime;
    this->leaveStickerQueueTime = hacker.leaveStickerQueueTime;
    this->leaveHoodieQueueTime = hacker.leaveHoodieQueueTime;
    this->totalWaitingTime = hacker.totalWaitingTime;
    this->enterStickerTime = hacker.enterStickerTime;
    this->turnAroundTime = hacker.turnAroundTime;

    for (int i = 0; i < hacker.commitTimes.size(); i++)
    {
        commitTimes.push_back(hacker.commitTimes[i]);
    }
    for (int i = 0; i < hacker.commitLines.size(); i++)
    {
        commitLines.push_back(hacker.commitLines[i]);
    }
    return *this;
}

int Hacker::getId() const {
    return this->id;
}

float Hacker::getArrivalTime() const {
    return arrivalTime;
}

float Hacker::getLeavingTime() const {
    return leavingTime;
}

int Hacker::getCommitCount() const {
    int commitCount = 0;
    for (int i = 0; i < commitTimes.size(); i++)
    {
        if (commitTimes[i] <= leaveStickerTime)
            commitCount++;
    }
    return commitCount;
}

vector<float> Hacker::getCommitTimes() const {
    return commitTimes;
}

vector<int> Hacker::getCommitLines() const {
    return commitLines;
}

void Hacker::setLeavingTime(float leavingTime) {
    this->leavingTime = leavingTime;
}

Hacker::Hacker() {
}

bool Hacker::operator<(const Hacker& rhs) const {
    if (this->getCommitCount() != rhs.getCommitCount())
        return this->getCommitCount() < rhs.getCommitCount();
    else
        return this->leaveStickerTime > rhs.leaveStickerTime;
}

bool Hacker::operator>(const Hacker& rhs) const {
    if (this->getCommitCount() != rhs.getCommitCount())
        return rhs.getCommitCount() < this->getCommitCount();
    else
        return this->leaveStickerTime < rhs.leaveStickerTime;
}

