#pragma once
#include<QtWidgets/QMainWindow>
#include<QListView>
#include<QMessageBox>
#include<bitset>
#include<QUdpSocket>
#include<QTextEdit>
#include"ui_DeviceVS.h"

class GroupTwo;
class GroupThree;
class FileSys;

//Основной класс, хранит группу регистров 1
class DeviceVS : public QMainWindow
{
    Q_OBJECT
public:
    DeviceVS(QWidget *parent = nullptr);
    ~DeviceVS();

//Поля
private:
    GroupTwo* m_pGroupTwo;
    GroupThree* m_pGroupThree;
    FileSys* m_pFs;

    QUdpSocket* m_pUdpSock;
    QTextEdit* m_txtEdt;
    QIntValidator* m_pValidRG5;

    //Объект для работы с данными
    QByteArray data;
    
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

    const uint16_t PORT_READ = 5555;
    const uint16_t PORT_WRITE = 4444;

public:
    Ui::DeviceVSClass ui;
    //Массив байт для хранения значений регистров
    QByteArray m_reg;

//Слоты
private slots:
    void slotRecievRequest();
    void slotOpenLog();
    void slotSaveSettings();
    void slotLoadSettings();

    //Группа регистров 1
    void slotEditReg0L();
    void slotEditReg0H();
    void slotEditReg1();
    void slotEditReg5Reg6();
    void slotEditReg7_0();
    void slotEditReg7_4();

//Методы
private:
    void updateInfo();
    void initReg();
    char binaryStringToInt(const QString& str);
    QByteArray readData(const uint8_t groupReg);
    QByteArray writeData(QByteArray& reg, const uint8_t groupReg);
    void initAllReg();
};
