#include "brennand.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Brennand w;
    w.show();

    return a.exec();
}
