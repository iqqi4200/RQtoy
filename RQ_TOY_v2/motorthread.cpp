#include "motorthread.h"

MotorThread::MotorThread(uint ID, QObject *parent) : QThread(parent)
{
    this->socketDescriptor = ID;
    SocketNumber = ID;
}
void MotorThread::run()
{
    while(!Stoped)
    {
        //thread starts here
        qDebug() << socketDescriptor << "Starting here";
        socket = new QTcpSocket();
        if(!socket->setSocketDescriptor(this->socketDescriptor))
        {
            emit error(socket->error());
            return;
        }
        connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
        connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);

        qDebug() << socketDescriptor << "Client Connection";
        RPI_Command.resize(4);

        exec();
    }
}

void MotorThread::readyRead()
{
    RPI_Reply = socket->readAll();
    RPI_Reply = RPI_Reply.trimmed();
    qDebug() << "-----------------------";
    socket->write(RPI_Command);
    if(RPI_Reply != "")qDebug() << "Data in:" << RPI_Reply;
    msleep(5000);
}
void MotorThread::disconnected()
{
    qDebug() << socketDescriptor << "DisConnection:";
    socket->deleteLater();
    exit(0);
}
void MotorThread::RPI_COMMAND(QString Mode, QString Motion, uint PWM)
{
    RPI_Command[0] = 0xC0;
    if(Mode == 0x01)//to answer
    {
        RPI_Command[1] = Mode.toInt();
        RPI_Command[2] = 0x00;
        RPI_Command[3] = 0x00;
    }else if(Mode == 0x02)//to output PWM and Motion
    {
        RPI_Command[1] = Mode.toInt();
        if(Motion == 0x01)
        {
            RPI_Command[2] = Motion.toInt();
            RPI_Command[3] = PWM;
        }
        else if(Motion == 0x02)
        {
            RPI_Command[2] = Motion.toInt();
            RPI_Command[3] = PWM;
        }
        else RPI_Command[3] = 0x00;
    }
    //socket->write(RPI_Command);

    qDebug() << RPI_Command;

}
void MotorThread::STOP_Thread()
{
    Stoped = true;
}
void MotorThread::START_Thread()
{
    Stoped = false;
}
