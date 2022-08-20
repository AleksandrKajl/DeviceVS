#pragma once
#include <QtWidgets/QMainWindow>
#include<QStringListModel>
#include<QListView>
#include<bitset>
#include<QUdpSocket>

#include "ui_DeviceVS.h"

class GroupTwo;
class GroupThree;

class DeviceVS : public QMainWindow
{
    Q_OBJECT
public:
    DeviceVS(QWidget *parent = nullptr);
    ~DeviceVS();

    DeviceVS* getPtr();

private:
    GroupTwo* m_pGroupTwo;
    GroupThree* m_pGroupThree;
    QUdpSocket* m_udpSock;
    QIntValidator* m_pValidRG5;

public:
    Ui::DeviceVSClass ui;

    //Массив байт для хранения значений регистров
    std::array<unsigned char, 40> m_reg{ 0 };

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

private:
    void updateInfo();
    void initReg();
    char binaryStringToInt(QString str);

};
