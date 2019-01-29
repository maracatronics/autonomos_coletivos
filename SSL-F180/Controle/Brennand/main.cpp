#include "brennand.h"
#include <QApplication>
#include <iostream>
#include <iomanip>  // Includes std::hex
#include "crc.h"

//int DRIBLE = 16, CHUTE = 64, PASSE = 32;

#define SIZE_COMANDS 9
#define SIZE_PROTOCOL SIZE_COMANDS+2

using std::cout;
using std::endl;



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Brennand w;
    w.show();
    return a.exec();
}



