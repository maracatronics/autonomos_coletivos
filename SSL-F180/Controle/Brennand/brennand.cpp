#include "brennand.h"
#include "ui_brennand.h"
#include "serialconnection.h"
#include "robot.h"
#include "iostream"
#include "ser.h"
#include <thread>
#include <QThread>
#define BR_SERIAL 9600

using namespace std;

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

    ui->boxDevice->addItem("No Port Connected");
    devSerial = new QSerialPort();
    procSerial = new serialConnection(devSerial);

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

void Brennand::CriaRobo(ser *s){
    QElapsedTimer timer_transmissao;
    QElapsedTimer timer_procura;
    bool startTime_transmissao = true;
    bool startTime_procura = true;

    while(true){
        if(iniciouTransmissao){
            if(startTime_transmissao){
                timer_transmissao.start();
                startTime_transmissao = false;
            }

            if(timer_transmissao.hasExpired(TAXA_TRANSMISSAO)){
                emit s->transmitindo();

                startTime_transmissao = true;
            }
        }

        if(!controlePorta){
            if(startTime_procura){
                timer_procura.start();
                startTime_procura = false;
            }

            if(timer_procura.hasExpired(1000)){
                qDebug() << "cheguei aqui";
                emit s->procurando();

                startTime_procura = true;
            }
        }
    };
}

void Brennand::procurarPortas(){
    QStringList listPorts = procSerial->loadPorts();
    ui->boxDevice->clear();
    if(listPorts.isEmpty()) ui->boxDevice->addItem("No Port Connected");
    else ui->boxDevice->addItems(listPorts);
}

void Brennand :: enviaComando(){
    Robot robo(1);
    unsigned char val1, val2,val3;
    //std::thread tRobo1;
    val1 = velMotor(ui->checkBox_17->isChecked(),ui->slider_motor1->value());
    val2 = velMotor(ui->checkBox_18->isChecked(),ui->slider_motor2->value());
    val3 = velMotor(ui->checkBox_19->isChecked(),ui->slider_motor3->value());

    robo.mountPackage(0, val1, val2, val3);
    //QThread *t1 = QThread::create(&Brennand::enviaComando, ref(*w));
    //QThread *t2 = QThread::create(&QSerialPort::write, ref(*devSerial), robo.protocol, sizeof(robo.protocol));
    devSerial->write(robo.protocol, sizeof(robo.protocol));
}

bool Brennand::comecouTransmissao(){
    return this->iniciouTransmissao;
}


