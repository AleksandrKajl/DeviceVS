#include"GroupThree.h"
#include<QMessageBox>

GroupThree::GroupThree(DeviceVS* pDevice)
	: m_pDev(pDevice)
{
    //������ ��������� ���
    connect(m_pDev->ui.lineEdit_23, SIGNAL(editingFinished()), SLOT(slotEditReg32_0()));
    connect(m_pDev->ui.lineEdit_24, SIGNAL(editingFinished()), SLOT(slotEditReg32_2_1()));
    connect(m_pDev->ui.lineEdit_25, SIGNAL(editingFinished()), SLOT(slotEditReg32_4_3()));
    connect(m_pDev->ui.lineEdit_26, SIGNAL(editingFinished()), SLOT(slotEditReg32_5()));
    connect(m_pDev->ui.lineEdit_27, SIGNAL(editingFinished()), SLOT(slotEditReg33()));
    connect(m_pDev->ui.lineEdit_28, SIGNAL(editingFinished()), SLOT(slotEditReg34_0()));
    connect(m_pDev->ui.lineEdit_29, SIGNAL(editingFinished()), SLOT(slotEditReg34_1()));
    connect(m_pDev->ui.lineEdit_30, SIGNAL(editingFinished()), SLOT(slotEditReg34_2()));
    connect(m_pDev->ui.lineEdit_31, SIGNAL(editingFinished()), SLOT(slotEditReg34_3()));
}

void GroupThree::slotEditReg32_0()
{
    std::bitset<6> rg32(m_pDev->m_reg[32]);
    rg32[0] = m_pDev->ui.lineEdit_23->text().toInt();
    m_pDev->m_reg[32] = rg32.to_ulong();

    updateInfo();
}

void GroupThree::slotEditReg32_2_1()
{
    std::bitset<6> rg32(m_pDev->m_reg[32]);
    bool res;
    char twoBit = m_pDev->ui.lineEdit_24->text().toInt(&res, 2);
    if (!res)
        QMessageBox::warning(nullptr, "Warning lineEdit_2", "�� �������� ��������� ������ � �����");

    switch (twoBit)
    {
    case(0):
        rg32[1] = 0;
        rg32[2] = 0;
        break;
    case(1):
        rg32[1] = 1;
        rg32[2] = 0;
        break;
    case(2):
        rg32[1] = 0;
        rg32[2] = 1;
        break;
    case(3):
        rg32[1] = 1;
        rg32[2] = 1;
    }

    m_pDev->m_reg[32] = rg32.to_ulong();
    updateInfo();
}

void GroupThree::slotEditReg32_4_3()
{
    std::bitset<6> rg32(m_pDev->m_reg[32]);
    bool res;
    char twoBit = m_pDev->ui.lineEdit_25->text().toInt(&res, 2);
    if (!res)
        QMessageBox::warning(nullptr, "Warning lineEdit_2", "�� �������� ��������� ������ � �����");

    switch (twoBit)
    {
    case(0):
        rg32[3] = 0;
        rg32[4] = 0;
        break;
    case(1):
        rg32[3] = 1;
        rg32[4] = 0;
        break;
    case(2):
        rg32[3] = 0;
        rg32[4] = 1;
        break;
    case(3):
        rg32[3] = 1;
        rg32[4] = 1;
    }

    m_pDev->m_reg[32] = rg32.to_ulong();

    updateInfo();
}

void GroupThree::slotEditReg32_5()
{
    std::bitset<6> rg32(m_pDev->m_reg[32]);
    rg32[5] = m_pDev->ui.lineEdit_26->text().toInt();
    m_pDev->m_reg[32] = rg32.to_ulong();

    updateInfo();
}

void GroupThree::slotEditReg33()
{
    char rg33 = m_pDev->ui.lineEdit_27->text().toInt();
    if (rg33 > 255)
        m_pDev->m_reg[33] = 255;
    else
        m_pDev->m_reg[33] = rg33;

    updateInfo();
}

void GroupThree::slotEditReg34_0()
{
    std::bitset<4> rg34(m_pDev->m_reg[34]);
    rg34[0] = m_pDev->ui.lineEdit_28->text().toInt();
    m_pDev->m_reg[34] = rg34.to_ulong();

    updateInfo();
}

void GroupThree::slotEditReg34_1()
{
    std::bitset<4> rg34(m_pDev->m_reg[34]);
    rg34[1] = m_pDev->ui.lineEdit_29->text().toInt();
    m_pDev->m_reg[34] = rg34.to_ulong();

    updateInfo();
}

void GroupThree::slotEditReg34_2()
{
    std::bitset<4> rg34(m_pDev->m_reg[34]);
    rg34[2] = m_pDev->ui.lineEdit_30->text().toInt();
    m_pDev->m_reg[34] = rg34.to_ulong();

    updateInfo();
}

void GroupThree::slotEditReg34_3()
{
    std::bitset<4> rg34(m_pDev->m_reg[34]);
    rg34[3] = m_pDev->ui.lineEdit_31->text().toInt();
    m_pDev->m_reg[34] = rg34.to_ulong();

    updateInfo();
}

void GroupThree::initReg()
{
    //������������� ������ ��������� ���
    std::bitset<6> rg32(m_pDev->m_reg[32]);
    QString str = QString::fromStdString(rg32.to_string());
    m_pDev->ui.lineEdit_23->setText(str[5]);
    m_pDev->ui.lineEdit_23->setInputMask("B");
    //ui.lineEdit_24->setText("11");
    m_pDev->ui.lineEdit_24->setText(str.sliced(3, 2));
    m_pDev->ui.lineEdit_24->setInputMask("bb");
    m_pDev->ui.lineEdit_25->setText(str.sliced(1, 2));
    m_pDev->ui.lineEdit_25->setInputMask("bb");
    m_pDev->ui.lineEdit_26->setText(str[0]);
    m_pDev->ui.lineEdit_26->setInputMask("B");
    m_pDev->ui.lineEdit_27->setText(QString::number(m_pDev->m_reg[33]));
    m_pDev->ui.lineEdit_27->setInputMask("000");
    std::bitset<4> rg34(m_pDev->m_reg[34]);
    str = QString::fromStdString(rg34.to_string());
    m_pDev->ui.lineEdit_28->setText(str[3]);
    m_pDev->ui.lineEdit_28->setInputMask("B");
    m_pDev->ui.lineEdit_29->setText(str[2]);
    m_pDev->ui.lineEdit_29->setInputMask("B");
    m_pDev->ui.lineEdit_30->setText(str[1]);
    m_pDev->ui.lineEdit_30->setInputMask("B");
    m_pDev->ui.lineEdit_31->setText(str[0]);
    m_pDev->ui.lineEdit_31->setInputMask("B");
}

void GroupThree::updateInfo()
{
    //��32[D0]
    if (m_pDev->m_reg[32] & 1)
    {
        m_pDev->ui.label_55->setText("����� ��������");
        m_pDev->ui.label_55->setStyleSheet("QLabel { background-color : green; color : black; }");
    }
    else
    {
        m_pDev->ui.label_55->setText("����� �� ��������");
        m_pDev->ui.label_55->setStyleSheet("QLabel { background-color : red; color : black; }");
    }

    //��32[D2:D1]
    char twoBit = (m_pDev->m_reg[32] >> 1) & 3;

    switch (twoBit)
    {
    case(0):
        m_pDev->ui.label_57->setText("������: �����");
        m_pDev->ui.label_57->setStyleSheet("QLabel { background-color : green; color : black; }");
        break;
    case(1):
        m_pDev->ui.label_57->setText("������: ��������������");
        m_pDev->ui.label_57->setStyleSheet("QLabel { background-color : yellow; color : black; }");
        break;
    case(2):
        m_pDev->ui.label_57->setText("������: ������");
        m_pDev->ui.label_57->setStyleSheet("QLabel { background-color : red; color : black; }");
    }

    //��32[D4:D3]
    twoBit = (m_pDev->m_reg[32] >> 3) & 3;

    switch (twoBit)
    {
    case(0):
        m_pDev->ui.label_59->setText("�����: �����");
        m_pDev->ui.label_59->setStyleSheet("QLabel { background-color : green; color : black; }");
        break;
    case(1):
        m_pDev->ui.label_59->setText("�����: ��������������");
        m_pDev->ui.label_59->setStyleSheet("QLabel { background-color : yellow; color : black; }");
        break;
    case(2):
        m_pDev->ui.label_59->setText("�����: ������");
        m_pDev->ui.label_59->setStyleSheet("QLabel { background-color : red; color : black; }");
    }

    //��32[D5]
    if (m_pDev->m_reg[32] >> 5)
    {
        m_pDev->ui.label_61->setText("������� ����������: ����");
        m_pDev->ui.label_61->setStyleSheet("QLabel { background-color : green; color : black; }");
    }
    else
    {
        m_pDev->ui.label_61->setText("������� ����������: ���");
        m_pDev->ui.label_61->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    }

    //��33
    if (m_pDev->m_reg[33] >= 170)
        m_pDev->ui.label_62->setStyleSheet("QLabel { background-color : green; color : black; }");
    else if (m_pDev->m_reg[33] >= 85)
        m_pDev->ui.label_62->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    else
        m_pDev->ui.label_62->setStyleSheet("QLabel { background-color : red; color : black; }");

    std::bitset<4> rg34(m_pDev->m_reg[34]);
    //��34[D0]
    if (rg34[0])
    {
        m_pDev->ui.label_65->setText("����� � ��������� �1: ����");
        m_pDev->ui.label_65->setStyleSheet("QLabel { background-color : green; color : black; }");
    }
    else
    {
        m_pDev->ui.label_65->setText("����� � ��������� �1: ���");
        m_pDev->ui.label_65->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    }


    //��34[D1]
    if (rg34[1])
    {
        m_pDev->ui.label_67->setText("����� � ��������� �2: ����");
        m_pDev->ui.label_67->setStyleSheet("QLabel { background-color : green; color : black; }");
    }
    else
    {
        m_pDev->ui.label_67->setText("����� � ��������� �2: ���");
        m_pDev->ui.label_67->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    }


    //��34[D2]
    if (rg34[2])
    {
        m_pDev->ui.label_71->setText("����� � ��������� �3: ����");
        m_pDev->ui.label_71->setStyleSheet("QLabel { background-color : green; color : black; }");
    }
    else
    {
        m_pDev->ui.label_71->setText("����� � ��������� �3: ���");
        m_pDev->ui.label_71->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    }


    //��34[D3]
    if (rg34[3])
    {
        m_pDev->ui.label_72->setText("����� � ��������� �4: ����");
        m_pDev->ui.label_72->setStyleSheet("QLabel { background-color : green; color : black; }");
    }
    else
    {
        m_pDev->ui.label_72->setText("����� � ��������� �4: ���");
        m_pDev->ui.label_72->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    }
}
