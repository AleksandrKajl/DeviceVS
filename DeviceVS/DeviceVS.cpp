#include "DeviceVS.h"

DeviceVS::DeviceVS(QWidget* parent)
    : QMainWindow(parent)
    , model(nullptr)
    , reg(nullptr)
    , view(new QListView(this))
{
    ui.setupUi(this);
    //reg.fill(0, 40);
    reg = new QList<QString>(40, 0);
    model = new QStringListModel(*reg, this);
    view->setModel(model);
    setCentralWidget(view);
    view->show();
}

DeviceVS::~DeviceVS()
{}
