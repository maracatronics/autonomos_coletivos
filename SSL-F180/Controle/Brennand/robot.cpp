#include "robot.h"
#include <iomanip>  // Includes std::hex
#include "crc.h"
//M id+flags V1 V2 V3 F CRC

Robot::Robot(int id)
{
    this->id=id;

}

void Robot::mountPackage(unsigned char flags, unsigned char v1, unsigned char v2, unsigned char v3){
    comands[0]='M';
    comands[1]=static_cast<unsigned char>(id+flags);
    comands[2]=v1;
    comands[3]=v2;
    comands[4]=v3;
    comands[5]='F';
    this->calcCRC(comands, sizeof (comands), protocol);
}

void Robot::calcCRC(unsigned char *comands, size_t tam, unsigned char *protocol) {
    std::copy(comands, comands + SIZE_COMANDS, protocol);
    uint16_t crc = CRC::Calculate(comands, tam, CRC::CRC_16_XMODEM());
    protocol[SIZE_PROTOCOL-2] = static_cast<unsigned char>((crc >> 8) & 0xff);
    protocol[SIZE_PROTOCOL-1] = static_cast<unsigned char>(crc & 0xff);
}
