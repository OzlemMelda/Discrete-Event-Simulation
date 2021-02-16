#include <iostream>
#include "simulation.h"

Simulation::Simulation(int N, int M, vector<float> stickerServiceTime, vector<float> hoodieServiceTime, vector<Hacker>* hackers, vector<int> attemptIds, vector<float> attemptTimes) : stickerNo(N), hoodieNo(M), stickerServiceTime(stickerServiceTime), hoodieServiceTime(hoodieServiceTime), hackers(*hackers), attemptIds(attemptIds), attemptTimes(attemptTimes){
    createSimulator();
};
Simulation::~Simulation() {
}

void Simulation::createSimulator() {
    //we get hacker informations from input and add their entry event to the event queue
    int M = attemptIds.size();

    for (int i = 0; i < M; i++) {
        int currentId = attemptIds[i];
        float currentAttemptTime = attemptTimes[i];
        //Hacker current = hackers[i];
        vector<float> commitTimes = hackers[currentId -1].getCommitTimes();
        vector<int> commitLines = hackers[currentId - 1].getCommitLines();
        int commitCount = 0;
        for (int j = 0; j < hackers[currentId-1].getCommitTimes().size(); j++)
        {
            if ((commitTimes[j] <= attemptTimes[i]) & (commitLines[j] >= 20))
            {
                commitCount++;
            }
        }
        if(commitCount >= 3){
            Event arrival(currentId, 'a', currentAttemptTime);
            events.push(arrival);
        }
        else if ((commitCount < 3)) {
            invalidStickerAttempt++;
        }
        if (i == (M - 1))
            lastTime = attemptTimes[i];
    }

    //create sticker desks and hoodie desks
    for (int i = 0; i < stickerNo; i++)
        stickers.push_back(Sticker(i, stickerServiceTime[i]));
    for (int i = 0; i < hoodieNo; i++)
        hoodies.push_back(Hoodie(i, hoodieServiceTime[i]));

    //the hacker id who left the system last
    int lastHackerId = -1;

    //stores the event that is popped from event queue
    int count = 0;
    while (!events.empty()) {

        /*a:entry to system
         c:exit from sticker
         q:exit from system
        */
        Event currentEvent = events.top();
        //*currentEvent = events.top();
        events.pop();

        char eventType = currentEvent.getEvent();
        float time = currentEvent.getTime();
        int hackerId = currentEvent.getHackerId();
        int currentServiceId = currentEvent.serviceId;

       /* count++;
        cout << "count: " << count << endl;
        cout << "eventType: " << eventType << endl;
        cout << "time: " << time << endl;
        cout << "hacker Id: " << hackerId << endl;
        cout << "hacker: " << hackers[hackerId - 1].getId() << " gift count: " << hackers[hackerId-1].giftCount << endl;
        cout << "current Service Id: " << currentServiceId << endl << endl;*/
        
        if ((eventType == 'a') & (hackers[hackerId-1].giftCount<6)) {
            //entry event
            bool isFree = false;
            int i = 0;
            
            //check if there is an available sticker desk
            for (; i < stickerNo && stickerQueue.empty(); i++) {
                if (!stickers[i].isBusy) {
                    isFree = true;
                    break;
                }
                else isFree = false;
            }

            if (isFree) {
                //a sticker desk is available
                stickers[i].runningTime += stickers[i].serviceTime;//increase sticker desk running time
                stickers[i].isBusy = true; //set sticker desk busy
                events.push(Event(hackerId, 'c', time + stickers[i].serviceTime, i));//create an exit from sticker desk event for current hacker and push event queue
                // get leaving time from sticker desk for current commit count 
                // just count commits when leaving from sticker desk occured
                hackers[hackerId - 1].enterStickerTime = time;
                hackers[hackerId-1].leaveStickerTime = time + stickers[i].serviceTime;
                hackers[hackerId-1].giftCount++;
            }
            else {
                //all sticker desks are busy so we push hacker to sticker queue
                stickerQueue.push(hackerId);
                hackers[hackerId - 1].enterStickerTime = time;
                hackers[hackerId-1].enterStickerQueueTime = time;
                if (maxStickerQueueLength < stickerQueue.size())
                    maxStickerQueueLength = stickerQueue.size();
                //cout << "max sticker queue length: " << maxStickerQueueLength;
            }

        }
        else if ((eventType == 'a') & (hackers[hackerId - 1].giftCount >= 6)) {
            invalidGiftAttempt++;
        }
        else if (eventType == 'c') {
            //exit from sticker queue
            if (!stickerQueue.empty()) {
                //Steps for taking new hacker from queue and allocating them to decent sticker service desk
                int newHackerId = stickerQueue.front();
                stickerQueue.pop();
                stickers[currentServiceId].runningTime += stickers[currentServiceId].serviceTime;
                stickers[currentServiceId].isBusy = true;
                events.push(Event(newHackerId, 'c', time + stickers[currentServiceId].serviceTime, currentServiceId));
                hackers[newHackerId-1].leaveStickerTime = time + stickers[currentServiceId].serviceTime;
                hackers[newHackerId-1].leaveStickerQueueTime = time;
                hackers[newHackerId-1].waitingStickerQueueTime += hackers[newHackerId-1].leaveStickerQueueTime - hackers[newHackerId-1].enterStickerQueueTime;
                hackers[newHackerId-1].giftCount++;
            }
            else {
                //if no hacker in queue then sticker desk is not busy
                stickers[currentServiceId].isBusy = false;
            }

            //Steps for the hacker who just exit sticker desk
            bool isFree = false;
            int i = 0;
            //check if hoodie desks are busy
            for (; i < hoodieNo && hoodieQueue.empty(); i++) {
                if (!hoodies[i].isBusy) {
                    isFree = true;
                    break;
                }
                else isFree = false;
            }
            if (isFree) {
                //a hoodie desk is available so create an exit from system event and push event queue
                hoodies[i].runningTime += hoodies[i].serviceTime;
                hoodies[i].isBusy = true;
                events.push(Event(hackerId, 'q', time + hoodies[i].serviceTime, i));
                hackers[hackerId-1].giftCount++;
                hackers[hackerId-1].setLeavingTime(time + hoodies[i].serviceTime);
                hackers[hackerId - 1].turnAroundTime += hackers[hackerId - 1].getLeavingTime() - hackers[hackerId - 1].enterStickerTime;

            }
            else {
                //all hoodie desks are busy so push hacker to hoodie queue
                hoodieQueue.push(hackers[hackerId-1]);
                //cout << "pushed to hooide queue: " << hackers[hackerId - 1].getId() << " at " << time << endl;
                hackers[hackerId-1].enterHoodieQueueTime = time;
                if (maxHoodieQueueLength < hoodieQueue.size())
                    maxHoodieQueueLength = hoodieQueue.size();
            }

        }
        else if (eventType == 'q') {
            //exit from system event
            if (!hoodieQueue.empty()) {
                //Steps for the hacker who was in hoodie queue
                int newHackerId = hoodieQueue.top().getId();
                hoodieQueue.pop();
                hoodies[currentServiceId].runningTime += hoodies[currentServiceId].serviceTime;
                events.push(Event(newHackerId, 'q', time + hoodies[currentServiceId].serviceTime, currentServiceId));
                hackers[newHackerId-1].leaveHoodieQueueTime = time;
                hackers[newHackerId-1].waitingHoodieQueueTime += hackers[newHackerId-1].leaveHoodieQueueTime - hackers[newHackerId-1].enterHoodieQueueTime;
                hackers[newHackerId-1].giftCount++;
                hackers[newHackerId-1].setLeavingTime(time + hoodies[currentServiceId].serviceTime);
                hackers[newHackerId - 1].turnAroundTime += hackers[newHackerId - 1].getLeavingTime() - hackers[newHackerId - 1].enterStickerTime;
            }
            else {
                //if no hacker in queue then hoodie desk is not busy
                hoodies[currentServiceId].isBusy = false;
            }

            //for the hacker who just left hoodie desk
            lastHackerId = hackerId;
            
        }
        if (lastTime < time)
            lastTime = time;
    }

}

const vector<Hacker>& Simulation::getHackers() const {
    return hackers;
}

const vector<Sticker>& Simulation::getStickers() const {
    return stickers;
}

const vector<Hoodie>& Simulation::getHoodies() const {
    return hoodies;
}

int Simulation::getMaxStickerQueueLength() const {
    return maxStickerQueueLength;
}

int Simulation::getMaxHoodieQueueLength() const {
    return maxHoodieQueueLength;
}

int Simulation::getInvalidStickerAttempCount() const {
    return invalidStickerAttempt;
}

int Simulation::getInvalidGiftAttempCount() const {
    return invalidGiftAttempt;
}

int Simulation::getGiftCount() const {
    int giftCount = 0;
    for (int i = 0; i < hackers.size(); i++)
    {
        giftCount += hackers[i].giftCount;
    }
    return giftCount;
}

float Simulation::getStickerQueueWaitingTime() const {
    float waitingStickerQueueTime = 0;
    for (int i = 0; i < hackers.size(); i++)
    {
         waitingStickerQueueTime += hackers[i].waitingStickerQueueTime;
    }
    return waitingStickerQueueTime;
}

float Simulation::getHoodieQueueWaitingTime() const {
    float waitingHoodieQueueTime = 0;
    for (int i = 0; i < hackers.size(); i++)
    {
        waitingHoodieQueueTime += hackers[i].waitingHoodieQueueTime;
    }
    return waitingHoodieQueueTime;
}

float Simulation::getTurnAroundTime() const {
    float turnAroundTime = 0;
    for (int i = 0; i < hackers.size(); i++)
    {   
        turnAroundTime += hackers[i].turnAroundTime;
    }
    return turnAroundTime;
}

void Simulation::getMostWaitingHacker(int* hacker, float* waitingTime) {
    *hacker = hackers.size();
    *waitingTime = 0;
    
    for (int i = 0; i < hackers.size(); i++)
    {
        hackers[i].totalWaitingTime = hackers[i].waitingStickerQueueTime + hackers[i].waitingHoodieQueueTime;
    }

    for (int i = 0; i < hackers.size(); i++)
    {
        if (hackers[i].totalWaitingTime == *waitingTime){
            if(hackers[i].getId() < *hacker){
                *waitingTime = hackers[i].totalWaitingTime;
                *hacker = hackers[i].getId();
            }
        }
        if ((hackers[i].totalWaitingTime > *waitingTime)) {
            *hacker = hackers[i].getId();
            *waitingTime = hackers[i].totalWaitingTime;
        }
    }
 }

void Simulation::getThreeGiftHacker(int* hacker, float* waitingTime) {
    *hacker = hackers.size()+1;
    *waitingTime = 100000000000000000;
    for (int i = 0; i < hackers.size(); i++)
    {
        if (hackers[i].giftCount == 6)
        {   
            if ((hackers[i].totalWaitingTime == *waitingTime)) {
                if (hackers[i].getId() < *hacker){
                    *hacker = hackers[i].getId();
                    *waitingTime = hackers[i].totalWaitingTime;
                }
            }

            if ((hackers[i].totalWaitingTime < *waitingTime)) {
                *hacker = hackers[i].getId();
                *waitingTime = hackers[i].totalWaitingTime;
            }
        }
    }
    if (*hacker == hackers.size()+1)
    {
        *hacker = -1;
        *waitingTime = -1;
    }
}

float Simulation::getTotalTime() const {
    return lastTime;
}