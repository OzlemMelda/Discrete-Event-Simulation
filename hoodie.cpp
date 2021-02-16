
#include "hoodie.h"

Hoodie::Hoodie(int id, float serviceTime) {
    this->id = id;
    this->serviceTime = serviceTime;
    this->runningTime = 0;
}

Hoodie::Hoodie(const Hoodie& hd) {
    this->id = hd.id;
    this->serviceTime = hd.serviceTime;
    this->runningTime = hd.runningTime;
}

Hoodie& Hoodie::operator=(const Hoodie& hd) {
    this->id = hd.id;
    this->isBusy = hd.isBusy;
    this->serviceTime = hd.serviceTime;
    this->runningTime = hd.runningTime;
    return *this;
}

Hoodie::~Hoodie() {
}