using namespace std;

#ifndef STICKER_H
#define STICKER_H


class Sticker {
    int id;

public:
    float runningTime;
    float serviceTime;
    bool isBusy = false;

    Sticker();
    Sticker(int id, float serviceTime);
    Sticker(const Sticker& stckr);
    Sticker& operator=(const Sticker& stckr);
    virtual ~Sticker();
};

#endif //STICKER_H
