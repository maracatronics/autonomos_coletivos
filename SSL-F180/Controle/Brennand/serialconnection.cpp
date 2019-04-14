#include "serialconnection.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <iostream>
#include <QThread>
using namespace std;

string GetStdoutFromCommand(string cmd);

serialConnection::serialConnection(QSerialPort *myDev)
{
    this->devSerial=myDev;
}

serialConnection::~serialConnection()
{}


QStringList serialConnection::loadPorts()
{
    QStringList devs;
    string name;

    name = system("whoami");

    GetStdoutFromCommand("ls -l /dev/ttyACM*");
    GetStdoutFromCommand("ls -l /dev/ttyUSB*");
    //GetStdoutFromCommand("sudo usermod -a -G dialout " + name);

    foreach (const QSerialPortInfo info, QSerialPortInfo::availablePorts()) {

        this->devSerial->setPort(info);

        if (this->devSerial->open(QIODevice::ReadWrite)) {
            this->devSerial->close();
            devs << info.portName();
        }

    }

    return devs;
}

string GetStdoutFromCommand(string cmd) {

    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");

    if (stream) {
        while (!feof(stream))

        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);

        pclose(stream);
    }
    return data;
}



/**
 * @brief serialConnection::connect
 *
 * Função que recebe os parametros Porta, BaudRate e FlowControl e realiza conexão
 *
 * @param QString Port(Porta Serial), uint32_t bd(BaudRate), uint8_t fc(FlowControl)
 * @return
 */
bool serialConnection::connect(QString Port, u_int32_t bd)
{
    // Device Serial Port
    devSerial->setPortName(Port);
    qDebug() << "Dispositivo Porta Serial: " << Port;


     // Conectar SerialPort

        // BaudRate
        switch (bd) {
        case 2400:
            qDebug() << "Baudrate: 2400";
            devSerial->setBaudRate(QSerialPort::Baud2400);
            break;
        case 4800:
            qDebug() << "Baudrate: 4800";
            devSerial->setBaudRate(QSerialPort::Baud4800);
            break;
        case 9600:
            qDebug() << "Baudrate: 9600";
            devSerial->setBaudRate(QSerialPort::Baud9600);
            break;
        case 19200:
            qDebug() << "Baudrate: 19200";
            devSerial->setBaudRate(QSerialPort::Baud19200);
            break;
        case 38400:
            qDebug() << "Baudrate: 38400";
            devSerial->setBaudRate(QSerialPort::Baud38400);
            break;
        case 115200:
            qDebug() << "Baudrate: 115200";
            devSerial->setBaudRate(QSerialPort::Baud115200);
            break;
        }

        // FlowControl
        devSerial->setFlowControl(QSerialPort::NoFlowControl);


        // Configurações adicionais
        devSerial->setDataBits(QSerialPort::Data8);
        devSerial->setParity(QSerialPort::NoParity);
        devSerial->setStopBits(QSerialPort::OneStop);


        if(devSerial->open(QIODevice::ReadWrite)) {
            qDebug() << "Porta serial aberta com sucesso!";
            return true;
        }
        else {
            qDebug() << "Falha ao abrir porta serial!";
            qDebug() << "Erro: " << devSerial->error();
            return false;
        }


}


/**
 * @brief serialConnection::disconnect
 *
 * Função Desconectar, realiza a limpeza do componente e fecha
 *
 * @param
 * @return
 */
bool serialConnection::disconnect()
{
    devSerial->clear();
    devSerial->close();


    if(devSerial->error() == 0 && !devSerial->isOpen()) {
        qDebug() << "Porta serial fechada com sucesso!";
        return true;
    }
    else {
        qDebug() << "Falha ao fechar a porta serial! ERRO: " << devSerial->error();
        return false;
    }

}


/**
 * @brief serialConnection::write
 *
 * Função para escrever na serial, recebe um ponteiro de caracteres já no formato do const char* do write
 *
 * @param const char *cmd
 * @return void
 */
qint64 serialConnection::write(const char *cmd)
{
    //std::cout << "oi";
    qint64 writeLength;

    writeLength = devSerial->write(cmd,qstrlen(cmd));
    //qDebug() << cmd;
    return writeLength;
}


/**
 * @brief serialConnection::Read
 *
 * Função Realiza a leitura do que chegar pela serial apos escrever na mesma, e devolve um QString
 *
 * @param
 * @return QString
 */
QString serialConnection::read()
{
     QString bufRxSerial;

     /* Awaits read all the data before continuing */
     while (devSerial->waitForReadyRead(20)) {
         bufRxSerial += devSerial->readAll();
     }
     return bufRxSerial;
}


/**
 * @brief serialConnection::read
 * Overloaded
 *
 * Função Realiza a leitura do que chegar pela serial apos escrever na mesma, e devolve uma QString
 * neste caso é enviado um inteiro com o numero de caracteres do buffer de recepção
 *
 * @param int
 * @return QString
 */
QString serialConnection::read(int TamanhoBuffer)
{
    char buf[TamanhoBuffer];

    if (devSerial->canReadLine()) {
        devSerial->read(buf, sizeof(buf));
    }

    return buf;

}
