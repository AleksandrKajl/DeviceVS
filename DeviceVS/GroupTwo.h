#pragma once
#include"DeviceVS.h"

//Класс для работы с группой регистров 2
class GroupTwo : public QObject
{
    Q_OBJECT
public:
	GroupTwo(DeviceVS* pDevice);
    void initReg();

public slots:
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

private:
    void updateInfo();
	
private:
	DeviceVS* m_pDev;
    QIntValidator* m_pValidReg8;
    QIntValidator* m_pValidReg9;
};
