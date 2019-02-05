#include "brennand.h"
#include <QApplication>
#include <iostream>
#include "crc.h"
#include <QThread>

//int DRIBLE = 16, CHUTE = 64, PASSE = 32;

void robotThread(Brennand &w);



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Brennand w;
    w.show();
    QThread *t1 = QThread::create(robotThread);
    t1->start();
    a.exec();
    return 0;
}

void robotThread(Brennand &w){
    using namespace std;
//    bool transmitindo = false;
//    std::thread tRobo1;
//    while (true) {
//        if(w.comecouTransmissao() && !transmitindo){
//            tRobo1 = std::thread(&Brennand::CriaRobo, &w, 1);
//            transmitindo = true;
//        }
//        else if(!w.comecouTransmissao() && transmitindo) {
//            transmitindo = false;
//            tRobo1.detach();
//        }
//    }

}



