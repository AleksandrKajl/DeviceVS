#include "DeviceVS.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DeviceVS w;
    w.show();
    return a.exec();
}
