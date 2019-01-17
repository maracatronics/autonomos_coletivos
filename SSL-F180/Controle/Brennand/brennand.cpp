#include "brennand.h"
#include "ui_brennand.h"

Brennand::Brennand(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Brennand)
{
    ui->setupUi(this);

}

Brennand::~Brennand()
{
    delete ui;
}
