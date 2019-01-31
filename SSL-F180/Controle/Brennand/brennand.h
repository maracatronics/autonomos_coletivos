#ifndef BRENNAND_H
#define BRENNAND_H

#include <QMainWindow>
#include "serialconnection.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include "ui_brennand.h"

#define INVERTIDO 128

namespace Ui {
class Brennand;
}

class Brennand : public QMainWindow
{
    Q_OBJECT

public:

    uint8_t protocol[5];

    explicit Brennand(QWidget *parent = nullptr);
    unsigned char velMotor(bool isChecked, int valorSlider);
    void controleThreads();
    static void CriaRobo(int id, unsigned char motor1, unsigned char motor2, unsigned char motor3);
    ~Brennand();

private slots:
    void on_slider_motor1_valueChanged(int value);

    void on_slider_motor2_valueChanged(int value);

    void on_slider_motor3_valueChanged(int value);

    void on_slider_motor1_2_valueChanged(int value);

    void on_slider_motor2_2_valueChanged(int value);

    void on_slider_motor1_3_valueChanged(int value);

    void on_slider_motor3_3_valueChanged(int value);

    void on_slider_motor2_3_valueChanged(int value);

    void on_slider_motor3_4_valueChanged(int value);

    void on_slider_motor1_4_valueChanged(int value);

    void on_slider_motor2_4_valueChanged(int value);

    void on_slider_motor3_2_valueChanged(int value);

    void on_vel_Motor1_textChanged(const QString &arg1);

    void on_vel_Motor2_textChanged(const QString &arg1);

    void on_vel_Motor3_textChanged(const QString &arg1);

    void on_vel_Motor1_2_textChanged(const QString &arg1);

    void on_vel_Motor2_2_textChanged(const QString &arg1);

    void on_vel_Motor3_2_textChanged(const QString &arg1);

    void on_vel_Motor1_3_textChanged(const QString &arg1);

    void on_vel_Motor2_3_textChanged(const QString &arg1);

    void on_vel_Motor3_3_textChanged(const QString &arg1);

    void on_vel_Motor1_4_textChanged(const QString &arg1);

    void on_vel_Motor2_4_textChanged(const QString &arg1);

    void on_vel_Motor3_4_textChanged(const QString &arg1);

    void on_iniciar_Button_clicked();

    void on_parar_Button_clicked();

    void on_connectButton_clicked();

    void on_disconnectButton_clicked();



    //static void CriaRobo(int id, QCheckBox &check1, QCheckBox &check2, QCheckBox &check3, QSlider &slider1, QSlider &slider2, QSlider &slider3 );




private:
    Ui::Brennand *ui;
    QStringList loadPorts();
    QSerialPort *devSerial;
    serialConnection *procSerial;
    bool controlePorta;
    bool controleTransmissao;
};

#endif // BRENNAND_H
