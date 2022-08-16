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

    //Массив байт для хранения значений регистров
    std::array<char, 40> reg{0};

    //массив для преобразования в шестнадцатиричное число
    std::array<char, 16> hexVal;

private slots:
    void editReg0L();
    void editReg0H();
    void editReg1();
    void editReg5();
    void editReg7_0();
    void editReg7_4();

private:
    void updateInfo();
    void initReg();
    char binaryStringToInt(QString str);



};
