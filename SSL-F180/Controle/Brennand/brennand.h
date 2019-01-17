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
    explicit Brennand(QWidget *parent = nullptr);
    ~Brennand();

private:
    Ui::Brennand *ui;
};

#endif // BRENNAND_H
