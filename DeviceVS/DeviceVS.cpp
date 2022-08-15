#include "DeviceVS.h"

DeviceVS::DeviceVS(QWidget* parent)
    : QMainWindow(parent)

{
    ui.setupUi(this);
    reg.fill(0, 40);
    
}

DeviceVS::~DeviceVS()
{}
