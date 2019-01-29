#ifndef ROBOT_H
#define ROBOT_H

#include "crc.h"
#define SIZE_COMANDS 9
#define SIZE_PROTOCOL SIZE_COMANDS+2

class Robot
{


private:
    int id;
    unsigned char comands[SIZE_COMANDS];
    unsigned char protocol[SIZE_PROTOCOL];

public:
    void mountPackage(unsigned char flags, unsigned char v1, unsigned char v2, unsigned char v3);
    Robot(int id);
    ~Robot();
    void calcCRC(unsigned char *comands, size_t tam, unsigned char *protocol);
};

#endif // ROBOT_H
