#pragma once
#include"DeviceVS.h"

class GroupThree : public QObject
{
	Q_OBJECT
public:
	GroupThree(DeviceVS* pDevice);

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
    void initReg();
    void updateInfo();

private:
    DeviceVS* m_pDev;
    QIntValidator* m_pValid;
};