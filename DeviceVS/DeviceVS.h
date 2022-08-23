#pragma once
#include <QtWidgets/QMainWindow>
#include<QStringListModel>
#include<QListView>
#include<bitset>
#include<QUdpSocket>

#include "ui_DeviceVS.h"

//#define REG_ALL 0
//#define REG_GROUP_1 1
//#define REG_GROUP_2 2
//#define REG_GROUP_3 3

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
    QUdpSocket* m_pUdpSock;
    QIntValidator* m_pValidRG5;

    //КОНСТАНТЫ ЗАПРОСОВ ДЛЯ УСТРОЙСТВА
    const uint8_t READ_REQ = 31;
    const uint8_t WRITE_REQ = 30;
    const uint8_t REQ_COMPLETED = 40;
    const uint8_t REQ_FAILED = 41;

    //КОНСТАНТЫ ДЛЯ ВЫБОРА ГРУППЫ РЕГИСТРОВ
    const uint8_t REG_ALL = 0;
    const uint8_t REG_GROUP_1 = 1;
    const uint8_t REG_GROUP_2 = 2;
    const uint8_t REG_GROUP_3 = 3;

public:
    Ui::DeviceVSClass ui;

    //Массив байт для хранения значений регистров
    QByteArray m_reg;


private slots:
    void slotRecievRequest();
    //void slotSendData();
    void openLog();

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
    QByteArray readData(const uint8_t groupReg);
    QByteArray writeData(QByteArray& reg, const uint8_t groupReg);

};
