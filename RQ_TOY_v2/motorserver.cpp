#include "motorserver.h"

//git test ver.1.0
MotorServer::MotorServer(QObject *parent) : QTcpServer(parent)
{

}


void MotorServer::StartServer()
{
    if(!this->listen(QHostAddress::Any,9527))
    {
        qDebug() << "Could not start server";
        qDebug() << this->errorString();
    }
    else
    {
        qDebug() << "Listening..." ;
    }
}

void MotorServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting...";
    ID = socketDescriptor;
    qDebug() << "ID = " << socketDescriptor;
    MotorThread *thread = new MotorThread(socketDescriptor,this);
    connect(thread, SIGNAL(finished()),thread, SLOT(deleteLater()));
    thread->start();
}
void MotorServer::CloseServer()
{
    this->close();
}
int MotorServer::Return_socketDescriptor()
{
    return ID;
}
