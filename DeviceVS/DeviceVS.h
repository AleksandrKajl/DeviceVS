#pragma once

#include <QtWidgets/QMainWindow>
#include<QStringListModel>
#include<QListView>
#include<QUdpSocket>
#include "ui_DeviceVS.h"

class TwoGroup;

class DeviceVS : public QMainWindow
{
    Q_OBJECT
public:
    DeviceVS(QWidget *parent = nullptr);
    ~DeviceVS();

    DeviceVS* getPtr();

private:
    TwoGroup* m_twoGroup;
    QUdpSocket* m_udpSock;

public:
    Ui::DeviceVSClass ui;

    //������ ���� ��� �������� �������� ���������
    std::array<unsigned char, 40> m_reg{ 0 };

private slots:
    void slotRecievRequest();
    void slotSendData();

    //������ ��������� 1
    void slotEditReg0L();
    void slotEditReg0H();
    void slotEditReg1();
    void slotEditReg5Reg6();
    void slotEditReg7_0();
    void slotEditReg7_4();

    //������ ��������� 3
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
