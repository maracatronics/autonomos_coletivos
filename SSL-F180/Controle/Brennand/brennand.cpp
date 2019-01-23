#include "brennand.h"
#include "ui_brennand.h"
#include "iostream"




Brennand::Brennand(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Brennand)
{
    ui->setupUi(this);
    ui->vel_Motor1->setText("0");
    ui->vel_Motor2->setText("0");
    ui->vel_Motor3->setText("0");

    ui->vel_Motor1_2->setText("0");
    ui->vel_Motor2_2->setText("0");
    ui->vel_Motor3_2->setText("0");

    ui->vel_Motor1_3->setText("0");
    ui->vel_Motor2_3->setText("0");
    ui->vel_Motor3_3->setText("0");

    ui->vel_Motor1_4->setText("0");
    ui->vel_Motor2_4->setText("0");
    ui->vel_Motor3_4->setText("0");



}

Brennand::~Brennand()
{
    delete ui;
}

void Brennand::on_slider_motor1_valueChanged(int value)
{
    QString valueString = QString::number(value);
    ui->vel_Motor1->setText(valueString);

}

void Brennand::on_slider_motor2_valueChanged(int value)
{
    QString valueString = QString::number(value);
    ui->vel_Motor2->setText(valueString);
}

void Brennand::on_slider_motor3_valueChanged(int value)
{
    QString valueString = QString::number(value);
    ui->vel_Motor3->setText(valueString);
}

void Brennand::on_slider_motor1_2_valueChanged(int value)
{
    QString valueString = QString::number(value);
    ui->vel_Motor1_2->setText(valueString);
}

void Brennand::on_slider_motor2_2_valueChanged(int value)
{
    QString valueString = QString::number(value);
    ui->vel_Motor2_2->setText(valueString);
}

void Brennand::on_slider_motor3_2_valueChanged(int value)
{
    QString valueString = QString::number(value);
    ui->vel_Motor3_2->setText(valueString);
}
void Brennand::on_slider_motor1_3_valueChanged(int value)
{
    QString valueString = QString::number(value);
    ui->vel_Motor1_3->setText(valueString);
}

void Brennand::on_slider_motor2_3_valueChanged(int value)
{
    QString valueString = QString::number(value);
    ui->vel_Motor2_3->setText(valueString);
}

void Brennand::on_slider_motor3_3_valueChanged(int value)
{
    QString valueString = QString::number(value);
    ui->vel_Motor3_3->setText(valueString);
}

void Brennand::on_slider_motor1_4_valueChanged(int value)
{
    QString valueString = QString::number(value);
    ui->vel_Motor1_4->setText(valueString);
}

void Brennand::on_slider_motor2_4_valueChanged(int value)
{
    QString valueString = QString::number(value);
    ui->vel_Motor2_4->setText(valueString);
}

void Brennand::on_slider_motor3_4_valueChanged(int value)
{
    QString valueString = QString::number(value);
    ui->vel_Motor3_4->setText(valueString);
}


void Brennand::on_vel_Motor1_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    if(value >= 0 && value <= 127)
        ui->slider_motor1->setValue(value);
}

void Brennand::on_vel_Motor2_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    if(value >= 0 && value <= 127)
        ui->slider_motor2->setValue(value);
}

void Brennand::on_vel_Motor3_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    if(value >= 0 && value <= 127)
        ui->slider_motor3->setValue(value);
}

void Brennand::on_vel_Motor1_2_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    if(value >= 0 && value <= 127)
        ui->slider_motor1_2->setValue(value);
}

void Brennand::on_vel_Motor2_2_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    if(value >= 0 && value <= 127)
        ui->slider_motor2_2->setValue(value);
}

void Brennand::on_vel_Motor3_2_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    if(value >= 0 && value <= 127)
        ui->slider_motor3_2->setValue(value);
}

void Brennand::on_vel_Motor1_3_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    if(value >= 0 && value <= 127)
        ui->slider_motor1_3->setValue(value);
}

void Brennand::on_vel_Motor2_3_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    if(value >= 0 && value <= 127)
        ui->slider_motor2_3->setValue(value);
}

void Brennand::on_vel_Motor3_3_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    if(value >= 0 && value <= 127)
        ui->slider_motor3_3->setValue(value);
}

void Brennand::on_vel_Motor1_4_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    if(value >= 0 && value <= 127)
        ui->slider_motor1_4->setValue(value);
}

void Brennand::on_vel_Motor2_4_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    if(value >= 0 && value <= 127)
        ui->slider_motor2_4->setValue(value);
}

void Brennand::on_vel_Motor3_4_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    if(value >= 0 && value <= 127)
        ui->slider_motor3_4->setValue(value);
}





