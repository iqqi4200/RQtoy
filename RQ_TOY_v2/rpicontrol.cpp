#include "rpicontrol.h"
#include "ui_rpicontrol.h"
#include "motordriver.h"

#define Serial_to_Arduino
RPIcontrol::RPIcontrol(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RPIcontrol)
{
    ui->setupUi(this);
    setWindowTitle("RPIcontrol");
    setFixedSize(550,350);
    menuBar()->setNativeMenuBar(false);
}

RPIcontrol::~RPIcontrol()
{
    delete ui;
}

void RPIcontrol::on_actionMotorDriver_triggered()
{
    Motor = new MotorDriver();
    Motor->show();

}
