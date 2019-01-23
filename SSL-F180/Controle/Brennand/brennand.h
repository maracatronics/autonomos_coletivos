#ifndef BRENNAND_H
#define BRENNAND_H

#include <QMainWindow>

namespace Ui {
class Brennand;
}

class Brennand : public QMainWindow
{
    Q_OBJECT

public:
    uint8_t protocol[5];

    explicit Brennand(QWidget *parent = nullptr);
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

private:
    Ui::Brennand *ui;
    QStringList loadPorts();
};

#endif // BRENNAND_H
