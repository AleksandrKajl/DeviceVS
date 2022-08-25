#pragma once
#include"DeviceVS.h"

////Класс для работы с группой регистров 3
class GroupThree : public QObject
{
	Q_OBJECT
public:
	GroupThree(DeviceVS* pDevice);
    void initReg();

public slots:
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

private:
    DeviceVS* m_pDev;
    QIntValidator* m_pValid;

    //Шесть бит регистра 32
    std::bitset<6> rg32;
    //Нужен для работы с четырьмя битами регистра 34
    std::bitset<4> rg34;

    //Константы для закрашивания полей с текстом
    const QString GREEN_FIELD = "QLabel { background-color : green; color : black; }";
    const QString YELLOW_FIELD = "QLabel { background-color : yellow; color : black; }";
    const QString RED_FIELD = "QLabel { background-color : red; color : black; }";
};