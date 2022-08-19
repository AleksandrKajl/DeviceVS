#pragma once

#include <QtWidgets/QMainWindow>
#include<QStringListModel>
#include<QListView>
#include<QUdpSocket>
#include "ui_DeviceVS.h"
#include"GroupTwo.h"
#include"GroupThree.h"

class DeviceVS : public QMainWindow
{
    Q_OBJECT
public:
    DeviceVS(QWidget *parent = nullptr);
    ~DeviceVS();

private:
    Ui::DeviceVSClass ui;
    GroupTwo* grTw;
    GroupThree* grTh;
    //Массив байт для хранения значений регистров
    std::array<unsigned char, 40> reg{0};

    QUdpSocket* udpSock;

private slots:
    void slotRecievRequest();

    void slotEditReg0L();
    void slotEditReg0H();
    void slotEditReg1();
    void slotEditReg5();
    void slotEditReg7_0();
    void slotEditReg7_4();

    void slotSendData();

private:
    void updateInfo();
    void initReg();
    char binaryStringToInt(QString str);



};
