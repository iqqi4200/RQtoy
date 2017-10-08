#ifndef MOTORTHREAD_H
#define MOTORTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <motordriver.h>
class MotorDriver;
class MotorThread : public QThread
{
    Q_OBJECT
    friend class MotorDriver;
public:
    explicit MotorThread(uint ID, QObject *parent = nullptr);
    void run();
    void RPI_COMMAND(QString, QString, uint);

    uint SocketNumber;
signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();
    void STOP_Thread();
    void START_Thread();
private:
    QTcpSocket *socket;
    uint socketDescriptor = 0;
    QByteArray  RPI_Reply;
    QByteArray  RPI_Command;
    MotorDriver *Driver;
    bool Stoped = false;
};

#endif // MOTORTHREAD_H
