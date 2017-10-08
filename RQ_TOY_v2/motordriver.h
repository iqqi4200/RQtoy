#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMessageBox>
#include <QStringRef>
#include <QApplication>

#include "motorserver.h"
#include <QTcpServer>
namespace Ui {
class MotorDriver;
}
class MotorThread;
class MotorServer;
class MotorDriver : public QWidget
{
    Q_OBJECT
    friend class MotorThread;
public:
    explicit MotorDriver(QWidget *parent = nullptr);
    ~MotorDriver();
signals:

public slots:

private slots:

    void PWMchange(int);
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

protected:
    void incomingconnection(qintptr socketDescriptor);
private:
    Ui::MotorDriver *ui;
    QSerialPort *arduino;
    QThread *OUTPUT_delay;

    uint PWM = 0;
    static const quint16 arduino_vendor_id = 9025;
    static const quint16 arduino_product_id = 67;
    QString arduinoPortName;
    bool arduino_connect = false;
    bool RunCheck = false;
    void updatetry(QString);
    MotorServer *Server;
    qintptr ID;
    QString Mode,Motion;
    void CHECK_btn();

};

#endif // MOTORDRIVER_H
