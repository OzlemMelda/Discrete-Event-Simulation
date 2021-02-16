
#include "sticker.h"

Sticker::Sticker(int id, float serviceTime) {
    this->id = id;
    this->serviceTime = serviceTime;
    this->runningTime = 0;
}

Sticker::Sticker(const Sticker& stckr) {
    this->id = stckr.id;
    this->serviceTime = stckr.serviceTime;
    this->runningTime = stckr.runningTime;
}

Sticker& Sticker::operator=(const Sticker& stckr) {
    this->id = stckr.id;
    this->isBusy = stckr.isBusy;
    this->serviceTime = stckr.serviceTime;
    this->runningTime = stckr.runningTime;
    return *this;
}

Sticker::~Sticker() {
}