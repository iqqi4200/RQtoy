#ifndef MOTORSERVER_H
#define MOTORSERVER_H

#include <QTcpServer>
#include <QDebug>
#include "motorthread.h"
class MotorServer : public QTcpServer
{
    Q_OBJECT
    friend class MotorDriver;
public:
    explicit MotorServer(QObject *parent = 0);
    void StartServer();
    void CloseServer();
    int Return_socketDescriptor();
    qintptr ID;
signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);
private:

};

#endif // MOTORSERVER_H
