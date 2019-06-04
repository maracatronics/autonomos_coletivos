#include "brennand.h"
#include <QApplication>
#include <iostream>
#include "crc.h"
#include <QObject>
#include <QThread>
#include <QSignalMapper>
#include "ser.h"
//int DRIBLE = 16, CHUTE = 64, PASSE = 32;

using namespace std;

void watchPorts();
void robotThread(Brennand &w);

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Brennand *w = new Brennand();
    w->show();
    ser s1,s2,s3,s4,s5;


    QSignalMapper* signalMapper = new QSignalMapper ();

    QObject::connect(&s1, SIGNAL(transmitindo()), signalMapper, SLOT(map()));
    QObject::connect(&s2, SIGNAL(transmitindo()), signalMapper, SLOT(map()));
    QObject::connect(&s3, SIGNAL(transmitindo()), signalMapper, SLOT(map()));
    QObject::connect(&s4, SIGNAL(transmitindo()), signalMapper, SLOT(map()));
    QObject::connect(&s5, SIGNAL(procurando()), w, SLOT(procurarPortas()));

    signalMapper->setMapping(&s1, 1);
    signalMapper->setMapping(&s2, 2);
    signalMapper->setMapping(&s3, 3);
    signalMapper->setMapping(&s4, 4);

    QObject::connect(signalMapper, SIGNAL(mapped(int)), w, SLOT(enviaComando(int)));

    QThread *t1 = QThread::create(&Brennand::CriaRobo, ref(*w), &s1, 1);
    t1->start();

    QThread *t2 = QThread::create(&Brennand::CriaRobo, ref(*w), &s2, 2);
    t2->start();

    QThread *t3 = QThread::create(&Brennand::CriaRobo, ref(*w), &s3, 3);
    t3->start();

    QThread *t4 = QThread::create(&Brennand::CriaRobo, ref(*w), &s4, 4);
    t4->start();

    QThread *t5 = QThread::create(&Brennand::InitProcura, ref(*w), &s5);
    t5->start();

    a.exec();
    return 0;
}



