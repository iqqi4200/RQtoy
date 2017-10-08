#include "motordriver.h"
#include "ui_motordriver.h"
//#define Serial_to_Arduino
#include "motorthread.h"
#include "motorserver.h"
MotorDriver::MotorDriver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MotorDriver)
{
    ui->setupUi(this);
    setWindowTitle("MotorDriver");
    setFixedSize(400,300);

#ifdef Serial_to_Arduino
    arduino = new QSerialPort;

    //server
    Server = new QTcpServer;


    /*qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier())
        {
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier())
        {
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }*/
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier())
        {
            if(serialPortInfo.vendorIdentifier() == arduino_vendor_id)
            {
                if(serialPortInfo.productIdentifier() == arduino_product_id)
                {
                    arduinoPortName = serialPortInfo.portName();
                    arduino_connect = true;
                }
            }
        }
    }
    if(arduino_connect)
    {
        arduino->setPortName(arduinoPortName);
        arduino->open(QSerialPort::WriteOnly);
        arduino->open(QSerialPort::ReadOnly);
        arduino->setBaudRate(QSerialPort::Baud115200);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }else
    {
        QMessageBox::warning(this,"Port error","Couldn't find the Arduino!","ok");

    }
#endif

    ui->horizontalSlider->setRange(0,255);
    ui->horizontalSlider->setValue(0);
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),
            ui->lcdNumber,SLOT(display(int)));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),
            this,SLOT(PWMchange(int)));
    ui->radioButton->setChecked(true);
    ui->radioButton_5->setChecked(true);
    ui->pushButton_3->setEnabled(false);
}
MotorDriver::~MotorDriver()
{
#ifdef Serial_to_Arduino
    if(arduino->isOpen())
    {
        arduino->close();
    }
#endif
    delete ui;
}

void MotorDriver::updatetry(QString Command)
{
#ifdef Serial_to_Arduino
    if(arduino->isWritable())
    {
        arduino->write(QString(Command).toStdString().c_str());

    }else
    {
        qDebug() << "Can't write in arduino";
    }
#endif
}
void MotorDriver::PWMchange(int value)
{
#ifdef Serial_to_Arduino
    if(RunCheck == true)
    {
        PWM = value;
        QString _PWM = QString::number(PWM);
        QString aa = "r,";
        MotorDriver::updatetry(aa.insert(2, _PWM + '\r'));
        OUTPUT_delay->msleep(2);
        //        if(arduino->isWritable())qDebug() << "u're running now";
    }else
    {
        MotorDriver::updatetry("r,0");
    }
    qDebug() << RunCheck;
#endif
    PWM = value;
    MotorThread *Thread = new MotorThread(ID,this);

    if(Mode == 0x02)
    {
        Server->Return_socketDescriptor();
        Thread->RPI_COMMAND(Mode, Motion, PWM);
    }
    delete Thread;
}


//void MotorDriver::on_checkBox_clicked()
//{
//    RunCheck = !RunCheck;
//}


void MotorDriver::on_pushButton_2_clicked()
{
    Server = new MotorServer(this);
    Server->StartServer();
    ID = Server->Return_socketDescriptor();
    MotorThread *Thread = new MotorThread(19,this);
    CHECK_btn();
    qDebug() << ID;
    qDebug() << Mode;
    qDebug() << Motion;
    qDebug() << PWM;
    if(!Thread->isRunning())
    {
        Thread->START_Thread();
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
    }
}

void MotorDriver::on_pushButton_3_clicked()
{
    //close server
    MotorThread *Thread = new MotorThread(19,this);

    if(Thread->isRunning())
    {
        Thread->STOP_Thread();
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(false);
    }
}
void MotorDriver::CHECK_btn()
{
    if(ui->radioButton->isChecked())
    {
        Mode = 0x01;
        qDebug() << "Mode = 0x01";
    }else Mode = 0x02;
    if(ui->radioButton_3->isChecked())
    {
        Motion = 0x01;
        qDebug() << "Motion = 0x01";
    }
    else if(ui->radioButton_4->isChecked())Motion = 0x02;
    else Motion = 0x03;

}
