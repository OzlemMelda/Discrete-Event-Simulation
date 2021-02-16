
#ifndef SIMULATION_H
#define SIMULATION_H


#include "hacker.h"
#include "event.h"
#include "hoodie.h"
#include "sticker.h"
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

class Simulation {
    int stickerNo;
    int hoodieNo;
    vector<float> stickerServiceTime;
    vector<float> hoodieServiceTime;
    vector<Hacker> hackers;
    vector<Sticker> stickers;
    vector<Hoodie> hoodies;
    vector<int> attemptIds;
    vector<float> attemptTimes;

    //customer id stored
    queue<int> stickerQueue;
    int maxStickerQueueLength = 0;

    //customers stored
    priority_queue<Hacker> hoodieQueue;
    int maxHoodieQueueLength = 0;

    priority_queue<Event> events;

    //working time of the System
    float workingTime = 0;
    int invalidStickerAttempt = 0;
    int invalidGiftAttempt = 0;
    float lastTime;

    void createSimulator();

public:

    Simulation(int N, int M, vector<float> stickerServiceTime, vector<float> hoodieServiceTime, vector<Hacker>* hackers, vector<int> attemptIds, vector<float> attemptTimes);
    Simulation(const Simulation& simulation);
    virtual ~Simulation();

    const vector<Hacker>& getHackers() const;
    const vector<Sticker>& getStickers() const;
    const vector<Hoodie>& getHoodies() const;

    int getMaxStickerQueueLength() const;
    int getMaxHoodieQueueLength() const;
    int getInvalidStickerAttempCount() const;
    int getInvalidGiftAttempCount() const;
    int getGiftCount() const;
    float getStickerQueueWaitingTime() const;
    float getHoodieQueueWaitingTime() const;
    float getTurnAroundTime() const;
    void getMostWaitingHacker(int* hacker, float* waitingTime);
    void getThreeGiftHacker(int* hacker, float* waitingTime);
    float getTotalTime() const;
};


#endif //SIMULATION_H