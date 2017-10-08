#ifndef RPICONTROL_H
#define RPICONTROL_H

#include <QMainWindow>
#include <motordriver.h>
namespace Ui {
class RPIcontrol;
}

class RPIcontrol : public QMainWindow
{
    Q_OBJECT

public:
    explicit RPIcontrol(QWidget *parent = 0);
    ~RPIcontrol();
    bool Open_Arduino = true;
private slots:
    void on_actionMotorDriver_triggered();

private:
    Ui::RPIcontrol *ui;
    MotorDriver *Motor;
    bool MotorWindowSwitch = false;
};

#endif // RPICONTROL_H
