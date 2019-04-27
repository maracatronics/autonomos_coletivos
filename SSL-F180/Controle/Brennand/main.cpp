#include "brennand.h"
#include <QApplication>
#include <iostream>
#include "crc.h"
#include <QObject>
#include <QThread>
#include "ser.h"
//int DRIBLE = 16, CHUTE = 64, PASSE = 32;

using namespace std;

void watchPorts();
void robotThread(Brennand &w);

//Brennand *w;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Brennand *w = new Brennand();
    w->show();
    ser s;

    QObject::connect(&s, SIGNAL(transmitindo()),
                     w, SLOT(enviaComando()));
    QObject::connect(&s, SIGNAL(procurando()),
                     w, SLOT(procurarPortas()));

    QThread *t1 = QThread::create(&Brennand::CriaRobo, ref(*w), &s);
    t1->start();

    a.exec();
    return 0;
}

/*void robotThread(Brennand &w){
    bool transmitindo = false;
    thread tRobo1;
    while (true) {
        if(w.comecouTransmissao() && !transmitindo){
            tRobo1 = thread(&Brennand::CriaRobo, ref(w), 1, ref(w));
            transmitindo = true;
        }
        else if(!w.comecouTransmissao() && transmitindo) {
            transmitindo = false;
            tRobo1.detach();
        }
    }    
}*/



