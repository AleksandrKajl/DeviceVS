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
    void slotSendData();

    //Группа регистров 1
    void slotEditReg0L();
    void slotEditReg0H();
    void slotEditReg1();
    void slotEditReg5Reg6();
    void slotEditReg7_0();
    void slotEditReg7_4();

    //Группа регистров 2
    void slotEditReg8();
    void slotEditReg9();
    void slotEditReg10_0();
    void slotEditReg10_1();
    void slotEditReg11();
    void slotEditReg12();
    void slotEditReg13_0();
    void slotEditReg13_1();
    void slotEditReg14();
    void slotEditReg15();
    void slotEditReg16_0();
    void slotEditReg16_1();
    void slotEditReg17();
    void slotEditReg18();
    void slotEditReg19_0();
    void slotEditReg19_1();

    //Группа регистров 3
    void slotEditReg32_0();
    void slotEditReg32_2_1();
    void slotEditReg32_4_3();
    void slotEditReg32_5();
    void slotEditReg33();
    void slotEditReg34_0();
    void slotEditReg34_1();
    void slotEditReg34_2();
    void slotEditReg34_3();

private:
    void updateInfo();
    void initReg();
    char binaryStringToInt(QString str);



};
