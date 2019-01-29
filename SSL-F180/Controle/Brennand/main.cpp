#include "brennand.h"
#include <QApplication>
#include <iostream>
#include <iomanip>  // Includes std::hex
#include "crc.h"

#define SIZE_COMANDS 9
#define SIZE_PROTOCOL SIZE_COMANDS+2

using std::cout;
using std::endl;

void calcCRC(unsigned char *comands, size_t tam, unsigned char *protocol);

int main(int argc, char *argv[])
{
    unsigned char comands[SIZE_COMANDS] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    unsigned char protocol[SIZE_PROTOCOL];

    QApplication a(argc, argv);
    Brennand w;
    w.show();

    calcCRC(comands, sizeof (comands), protocol);

//    for (int i=0; i < 9; i++) {
//        cout << *(protocol + i) << " ";
//    }
//    cout << std::hex << static_cast<int>(protocol[9]) << " ";
//    cout << std::hex << static_cast<int>(protocol[10]) << endl;

    return a.exec();
}


void calcCRC(unsigned char *comands, size_t tam, unsigned char *protocol) {
    std::copy(comands, comands + SIZE_COMANDS, protocol);
    uint16_t crc = CRC::Calculate(comands, tam, CRC::CRC_16_XMODEM());
    protocol[SIZE_PROTOCOL-2] = static_cast<unsigned char>((crc >> 8) & 0xff);
    protocol[SIZE_PROTOCOL-1] = static_cast<unsigned char>(crc & 0xff);
}
