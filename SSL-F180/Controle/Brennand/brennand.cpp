#include "brennand.h"
#include "ui_brennand.h"
#include "serialconnection.h"
#include "robot.h"
#include "iostream"

#define BR_SERIAL 32400


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
    controlePorta=false;
    controleTransmissao=false;
    iniciouTransmissao = false;

    devSerial = new QSerialPort(this);
    procSerial = new serialConnection(devSerial);
    QStringList dispSerial = procSerial->loadPorts();
    ui->boxDevice->addItems(dispSerial);

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


void Brennand::on_connectButton_clicked()
{
    procSerial->connect(ui->boxDevice->currentText(),BR_SERIAL);
    controlePorta=true;
}

void Brennand::on_disconnectButton_clicked()
{
    procSerial->disconnect();
    controlePorta=false;
}



void Brennand::on_iniciar_Button_clicked()
{
    controleTransmissao=true;
    if(controlePorta && controleTransmissao){
        qDebug()<<"trasmissão iniciada";
        iniciouTransmissao = true;
    }
    else if (!controlePorta && controleTransmissao){
        qDebug()<<"É preciso abrir a porta";
    }
}

void Brennand::on_parar_Button_clicked()
{
    controleTransmissao=false;
    if(controlePorta && !controleTransmissao){
        qDebug()<<"trasmissão parada";
        iniciouTransmissao = false;
    }
}

unsigned char Brennand::velMotor(bool isChecked, int valorSlider){
    return isChecked? static_cast<unsigned char>(valorSlider | INVERTIDO) : static_cast<unsigned char>(valorSlider);
}

void Brennand::CriaRobo(int id){
    Robot robo(id);
    enviaComando(robo);
}

void Brennand :: enviaComando(Robot robo){
    unsigned char val1, val2,val3;
    while (true) {
        val1 = velMotor(ui->checkBox_17->isChecked(),ui->slider_motor1->value());
        val2 = velMotor(ui->checkBox_18->isChecked(),ui->slider_motor2->value());
        val3 = velMotor(ui->checkBox_19->isChecked(),ui->slider_motor3->value());
        robo.mountPackage(0, val1, val2, val3);
        //qDebug() << "oi";
        devSerial->write(robo.protocol, sizeof (robo.protocol));
    }
}

bool Brennand::comecouTransmissao(){
    return this->iniciouTransmissao;
}


