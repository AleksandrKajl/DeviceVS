#pragma once

#include <QtWidgets/QMainWindow>
#include<QStringListModel>
#include<QListView>
#include "ui_DeviceVS.h"

class DeviceVS : public QMainWindow
{
    Q_OBJECT

public:
    DeviceVS(QWidget *parent = nullptr);
    ~DeviceVS();

private:
    Ui::DeviceVSClass ui;
    QByteArray reg;


};
