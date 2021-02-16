using namespace std;

#ifndef HOODIE_H
#define HOODIE_H


class Hoodie {
    int id;

public:
    float runningTime;
    float serviceTime;
    bool isBusy=false;

    Hoodie();
    Hoodie(int id, float serviceTime);
    Hoodie(const Hoodie& hd);
    Hoodie& operator=(const Hoodie& hd);
    virtual ~Hoodie();
};

#endif //HOODIE_H
