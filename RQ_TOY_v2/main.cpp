#include "rpicontrol.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RPIcontrol w;
    w.show();
    return a.exec();
}
