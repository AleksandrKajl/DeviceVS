#include "DeviceVS.h"
#include<bitset>
#include<QMessageBox>
#include"TwoGroup.h"

DeviceVS::DeviceVS(QWidget* parent)
    : QMainWindow(parent)
    , m_udpSock(new QUdpSocket(this))
    , m_twoGroup(new TwoGroup(this))
{
    ui.setupUi(this);
    this->setWindowTitle("Режим работы");

    m_udpSock->bind(5555);

    connect(m_udpSock, SIGNAL(readyRead()), SLOT(slotRecievRequest()));
    //ГРУППА РЕГИСТРОВ ОДИН
    connect(ui.lineEdit, SIGNAL(editingFinished()), SLOT(slotEditReg0L()));
    connect(ui.lineEdit_2, SIGNAL(editingFinished()), SLOT(slotEditReg0H()));
    connect(ui.lineEdit_3, SIGNAL(editingFinished()), SLOT(slotEditReg1()));
    connect(ui.lineEdit_4, SIGNAL(editingFinished()), SLOT(slotEditReg5Reg6()));
    connect(ui.lineEdit_5, SIGNAL(editingFinished()), SLOT(slotEditReg7_0()));
    connect(ui.lineEdit_6, SIGNAL(editingFinished()), SLOT(slotEditReg7_4()));
    //ГРУППА РЕГИСТРОВ ДВА
    //----------------Абонент 1-------------------------------------------------------------
    connect(ui.lineEdit_7, SIGNAL(editingFinished()), SLOT(slotEditReg8()));
    connect(ui.lineEdit_8, SIGNAL(editingFinished()), SLOT(slotEditReg9()));
    connect(ui.lineEdit_9, SIGNAL(editingFinished()), SLOT(slotEditReg10_0()));
    connect(ui.lineEdit_10, SIGNAL(editingFinished()), SLOT(slotEditReg10_1()));
    //======================================================================================
    //----------------Абонент 2-------------------------------------------------------------
    connect(ui.lineEdit_11, SIGNAL(editingFinished()), SLOT(slotEditReg11()));
    connect(ui.lineEdit_12, SIGNAL(editingFinished()), SLOT(slotEditReg12()));
    connect(ui.lineEdit_13, SIGNAL(editingFinished()), SLOT(slotEditReg13_0()));
    connect(ui.lineEdit_14, SIGNAL(editingFinished()), SLOT(slotEditReg13_1()));
    //======================================================================================
    //----------------Абонент 3-------------------------------------------------------------
    connect(ui.lineEdit_15, SIGNAL(editingFinished()), SLOT(slotEditReg14()));
    connect(ui.lineEdit_16, SIGNAL(editingFinished()), SLOT(slotEditReg15()));
    connect(ui.lineEdit_17, SIGNAL(editingFinished()), SLOT(slotEditReg16_0()));
    connect(ui.lineEdit_18, SIGNAL(editingFinished()), SLOT(slotEditReg16_1()));
    //======================================================================================
    //----------------Абонент 4-------------------------------------------------------------
    connect(ui.lineEdit_19, SIGNAL(editingFinished()), SLOT(slotEditReg17()));
    connect(ui.lineEdit_20, SIGNAL(editingFinished()), SLOT(slotEditReg18()));
    connect(ui.lineEdit_21, SIGNAL(editingFinished()), SLOT(slotEditReg19_0()));
    connect(ui.lineEdit_22, SIGNAL(editingFinished()), SLOT(slotEditReg19_1()));
    //======================================================================================
    //ГРУППА РЕГИСТРОВ ТРИ
    connect(ui.lineEdit_23, SIGNAL(editingFinished()), SLOT(slotEditReg32_0()));
    connect(ui.lineEdit_24, SIGNAL(editingFinished()), SLOT(slotEditReg32_2_1()));
    connect(ui.lineEdit_25, SIGNAL(editingFinished()), SLOT(slotEditReg32_4_3()));
    connect(ui.lineEdit_26, SIGNAL(editingFinished()), SLOT(slotEditReg32_5()));
    connect(ui.lineEdit_27, SIGNAL(editingFinished()), SLOT(slotEditReg33()));
    connect(ui.lineEdit_28, SIGNAL(editingFinished()), SLOT(slotEditReg34_0()));
    connect(ui.lineEdit_29, SIGNAL(editingFinished()), SLOT(slotEditReg34_1()));
    connect(ui.lineEdit_30, SIGNAL(editingFinished()), SLOT(slotEditReg34_2()));
    connect(ui.lineEdit_31, SIGNAL(editingFinished()), SLOT(slotEditReg34_3()));


    m_reg[0] = 33;
    m_reg[1] = 0x15;
    //Reg2 -Reg4 reserve
    m_reg[5] = 0x75;
    m_reg[6] = 0x30;
    m_reg[7] = 0X11;
    initReg();
}

DeviceVS::~DeviceVS()
{}

DeviceVS* DeviceVS::getPtr()
{
    return this;
}

void DeviceVS::slotRecievRequest()
{
    QByteArray data;
    do
    {
        data.resize(m_udpSock->pendingDatagramSize());
        m_udpSock->readDatagram(data.data(), data.size());
    } while (m_udpSock->hasPendingDatagrams());

    QDataStream in(&data, QIODevice::ReadOnly);
    int a, b;
    in >> a >> b;
}

//ГРУППА РЕГИСТРОВ 1
void DeviceVS::slotEditReg0L()
{
    m_reg[0] = (m_reg[0] & 0xF0) + binaryStringToInt(ui.lineEdit->text());
    updateInfo();
}


void DeviceVS::slotEditReg0H()
{
    m_reg[0] = (m_reg[0] & 0xF) + (binaryStringToInt(ui.lineEdit_2->text()) * 0x10);
    updateInfo();
}

void DeviceVS::slotEditReg1()
{
    QString str(ui.lineEdit_3->text());
    bool Ok;
    m_reg[1] = str.sliced(2).toInt(&Ok, 16);
    if (!Ok)
        return;
    updateInfo();
}

void DeviceVS::slotEditReg5Reg6()
{
    char16_t var = ui.lineEdit_4->text().toInt();
    m_reg[5] = var >> 8;
    m_reg[6] = var & 0xFF;
}

void DeviceVS::slotEditReg7_0()
{
    m_reg[7] = (m_reg[7] & 0xF0) + ui.lineEdit_5->text().toInt();
    updateInfo();
}

void DeviceVS::slotEditReg7_4()
{
    m_reg[7] = (m_reg[7] & 0xF) + (ui.lineEdit_6->text().toInt() << 4);
    updateInfo();
}


//ГРУППА РЕГИСТРОВ ДВА
//------------------Абонент 1--------------------------------
void DeviceVS::slotEditReg8()
{
    char rg8 = ui.lineEdit_7->text().toInt();
    if (rg8 > 100)
        m_reg[8] = 100;
    else
        m_reg[8] = rg8;
}

void DeviceVS::slotEditReg9()
{
    char rg9 = ui.lineEdit_8->text().toInt();
    if (rg9 > 10)
        m_reg[9] = 10;
    else
        m_reg[9] = rg9;
}

void DeviceVS::slotEditReg10_0()
{
    std::bitset<2> rg10(m_reg[10]);
    rg10[0] = ui.lineEdit_9->text().toInt();
    m_reg[10] = rg10.to_ulong();

    updateInfo();
}

void DeviceVS::slotEditReg10_1()
{
    std::bitset<2> rg10(m_reg[10]);
    rg10[1] = ui.lineEdit_10->text().toInt();
    m_reg[10] = rg10.to_ulong();

    updateInfo();
}

//=======================================================================
//----------------Абонент 2----------------------------------------------
void DeviceVS::slotEditReg11()
{
    char rg11 = ui.lineEdit_11->text().toInt();
    if (rg11 > 100)
        m_reg[11] = 100;
    else
        m_reg[11] = rg11;
}

void DeviceVS::slotEditReg12()
{
    char rg12 = ui.lineEdit_12->text().toInt();
    if (rg12 > 10)
        m_reg[12] = 10;
    else
        m_reg[12] = rg12;
}

void DeviceVS::slotEditReg13_0()
{
    std::bitset<2> rg13(m_reg[13]);
    rg13[0] = ui.lineEdit_13->text().toInt();
    m_reg[13] = rg13.to_ulong();

    updateInfo();
}

void DeviceVS::slotEditReg13_1()
{
    std::bitset<2> rg13(m_reg[13]);
    rg13[1] = ui.lineEdit_14->text().toInt();
    m_reg[13] = rg13.to_ulong();

    updateInfo();
}

//==================================================
//----------------Абонент 3-------------------------
void DeviceVS::slotEditReg14()
{
    char rg14 = ui.lineEdit_15->text().toInt();
    if (rg14 > 100)
        m_reg[14] = 100;
    else
        m_reg[14] = rg14;
}

void DeviceVS::slotEditReg15()
{
    char rg15 = ui.lineEdit_16->text().toInt();
    if (rg15 > 10)
        m_reg[15] = 10;
    else
        m_reg[15] = rg15;
}

void DeviceVS::slotEditReg16_0()
{
    std::bitset<2> rg16(m_reg[16]);
    rg16[0] = ui.lineEdit_17->text().toInt();
    m_reg[16] = rg16.to_ulong();

    updateInfo();
}

void DeviceVS::slotEditReg16_1()
{
    std::bitset<2> rg16(m_reg[16]);
    rg16[1] = ui.lineEdit_18->text().toInt();
    m_reg[16] = rg16.to_ulong();

    updateInfo();
}

//==================================================
//----------------Абонент 4-------------------------
void DeviceVS::slotEditReg17()
{
    char rg17 = ui.lineEdit_19->text().toInt();
    if (rg17 > 100)
        m_reg[17] = 100;
    else
        m_reg[17] = rg17;
}

void DeviceVS::slotEditReg18()
{
    char rg18 = ui.lineEdit_20->text().toInt();
    if (rg18 > 10)
        m_reg[18] = 10;
    else
        m_reg[18] = rg18;
}

void DeviceVS::slotEditReg19_0()
{
    std::bitset<2> rg19(m_reg[19]);
    rg19[0] = ui.lineEdit_21->text().toInt();
    m_reg[19] = rg19.to_ulong();

    updateInfo();
}

void DeviceVS::slotEditReg19_1()
{
    std::bitset<2> rg19(m_reg[19]);
    rg19[1] = ui.lineEdit_22->text().toInt();
    m_reg[19] = rg19.to_ulong();

    updateInfo();
}


//ГРУППА РЕГИСТРОВ ТРИ
void DeviceVS::slotEditReg32_0()
{
    std::bitset<6> rg32(m_reg[32]);
    rg32[0] = ui.lineEdit_23->text().toInt();
    m_reg[32] = rg32.to_ulong();

    updateInfo();
}

void DeviceVS::slotEditReg32_2_1()
{
    std::bitset<6> rg32(m_reg[32]);
    bool res;
    char twoBit = ui.lineEdit_24->text().toInt(&res, 2);
    if (!res)
        QMessageBox::warning(this, "Warning lineEdit_2", "Не возможно перевести строку в число");

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

    m_reg[32] = rg32.to_ulong();
    updateInfo();
}

void DeviceVS::slotEditReg32_4_3()
{
    std::bitset<6> rg32(m_reg[32]);
    bool res;
    char twoBit = ui.lineEdit_25->text().toInt(&res, 2);
    if (!res)
        QMessageBox::warning(this, "Warning lineEdit_2", "Не возможно перевести строку в число");

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

    m_reg[32] = rg32.to_ulong();

    updateInfo();
}

void DeviceVS::slotEditReg32_5()
{
    std::bitset<6> rg32(m_reg[32]);
    rg32[5] = ui.lineEdit_26->text().toInt();
    m_reg[32] = rg32.to_ulong();

    updateInfo();
}

void DeviceVS::slotEditReg33()
{
    char rg33 = ui.lineEdit_27->text().toInt();
    if (rg33 > 255)
        m_reg[33] = 255;
    else
        m_reg[33] = rg33;

    updateInfo();
}

void DeviceVS::slotEditReg34_0()
{
    std::bitset<4> rg34(m_reg[34]);
    rg34[0] = ui.lineEdit_28->text().toInt();
    m_reg[34] = rg34.to_ulong();

    updateInfo();
}

void DeviceVS::slotEditReg34_1()
{
    std::bitset<4> rg34(m_reg[34]);
    rg34[1] = ui.lineEdit_29->text().toInt();
    m_reg[34] = rg34.to_ulong();

    updateInfo();
}

void DeviceVS::slotEditReg34_2()
{
    std::bitset<4> rg34(m_reg[34]);
    rg34[2] = ui.lineEdit_30->text().toInt();
    m_reg[34] = rg34.to_ulong();

    updateInfo();
}

void DeviceVS::slotEditReg34_3()
{
    std::bitset<4> rg34(m_reg[34]);
    rg34[3] = ui.lineEdit_31->text().toInt();
    m_reg[34] = rg34.to_ulong();

    updateInfo();
}

void DeviceVS::slotSendData()
{
}

void DeviceVS::initReg()
{
    //ИНИЦИАЛИЗАЦИЯ ГРУППЫ РЕГИСТРОВ ОДИН
    //Reg0
    QString regStr = QString::fromStdString(std::bitset<8>(m_reg[0]).to_string());
    //Порядок бит в строке перевернут
    ui.lineEdit->setText(regStr.sliced(4, 4));
    ui.lineEdit->setInputMask("BBBB");
    ui.lineEdit_2->setText(regStr.sliced(0, 4));
    ui.lineEdit_2->setInputMask("BBBB");
    //Reg1
    ui.lineEdit_3->setText("0x" + QString::number(m_reg[1], 16));
    ui.lineEdit_3->setInputMask("NNhh");

    //Reg2 -Reg4 reserve
    //Reg5 - Reg6
    ui.lineEdit_4->setText(QString::number((m_reg[5] * 0x100) + m_reg[6]));      //Собираем значение из двух байт
    ui.lineEdit_4->setInputMask("99999");
    regStr = QString::fromStdString(std::bitset<8>(m_reg[7]).to_string());
    ui.lineEdit_5->setText(regStr[7]);
    ui.lineEdit_5->setInputMask("B");
    ui.lineEdit_6->setText(regStr[3]);
    ui.lineEdit_6->setInputMask("B");

    //ИНИЦИАЛИЗАЦИЯ ГРУППЫ РЕГИСТРОВ ДВА
//--------------------Абонент 1-----------------------------------------------
    ui.lineEdit_7->setText(QString::number(m_reg[8]));
    ui.lineEdit_7->setInputMask("000");
    ui.lineEdit_8->setText(QString::number(m_reg[9]));
    ui.lineEdit_8->setInputMask("00");
    QString str = QString::fromStdString(std::bitset<2>(m_reg[10]).to_string());
    ui.lineEdit_9->setText(str[1]);
    ui.lineEdit_9->setInputMask("B");
    ui.lineEdit_10->setText(str[0]);
    ui.lineEdit_10->setInputMask("B");
    //=============================================================================
    //---------------------Абонент 2-----------------------------------------------
    ui.lineEdit_11->setText(QString::number(m_reg[11]));
    ui.lineEdit_11->setInputMask("000");
    ui.lineEdit_12->setText(QString::number(m_reg[12]));
    ui.lineEdit_12->setInputMask("00");
    str = QString::fromStdString(std::bitset<2>(m_reg[13]).to_string());
    ui.lineEdit_13->setText(str[1]);
    ui.lineEdit_13->setInputMask("B");
    ui.lineEdit_14->setText(str[0]);
    ui.lineEdit_14->setInputMask("B");

    //=============================================================================
    //---------------------Абонент 3-----------------------------------------------
    ui.lineEdit_15->setText(QString::number(m_reg[14]));
    ui.lineEdit_15->setInputMask("000");
    ui.lineEdit_16->setText(QString::number(m_reg[15]));
    ui.lineEdit_16->setInputMask("00");
    str = QString::fromStdString(std::bitset<2>(m_reg[16]).to_string());
    ui.lineEdit_17->setText(str[1]);
    ui.lineEdit_17->setInputMask("B");
    ui.lineEdit_18->setText(str[0]);
    ui.lineEdit_18->setInputMask("B");

    //=============================================================================
    //---------------------Абонент 4-----------------------------------------------
    ui.lineEdit_19->setText(QString::number(m_reg[17]));
    ui.lineEdit_19->setInputMask("000");
    ui.lineEdit_20->setText(QString::number(m_reg[18]));
    ui.lineEdit_20->setInputMask("00");
    str = QString::fromStdString(std::bitset<2>(m_reg[19]).to_string());
    ui.lineEdit_21->setText(str[1]);
    ui.lineEdit_21->setInputMask("B");
    ui.lineEdit_22->setText(str[0]);
    ui.lineEdit_22->setInputMask("B");
    //=============================================================================

    //ИНИЦИАЛИЗАЦИЯ ГРУППЫ РЕГИСТРОВ ТРИ
    std::bitset<6> rg32(m_reg[32]);
    str = QString::fromStdString(rg32.to_string());
    ui.lineEdit_23->setText(str[5]);
    ui.lineEdit_23->setInputMask("B");
    //ui.lineEdit_24->setText("11");
    ui.lineEdit_24->setText(str.sliced(3, 2));
    ui.lineEdit_24->setInputMask("bb");
    ui.lineEdit_25->setText(str.sliced(1, 2));
    ui.lineEdit_25->setInputMask("bb");
    ui.lineEdit_26->setText(str[0]);
    ui.lineEdit_26->setInputMask("B");
    ui.lineEdit_27->setText(QString::number(m_reg[33]));
    ui.lineEdit_27->setInputMask("000");
    std::bitset<4> rg34(m_reg[34]);
    str = QString::fromStdString(rg34.to_string());
    ui.lineEdit_28->setText(str[3]);
    ui.lineEdit_28->setInputMask("B");
    ui.lineEdit_29->setText(str[2]);
    ui.lineEdit_29->setInputMask("B");
    ui.lineEdit_30->setText(str[1]);
    ui.lineEdit_30->setInputMask("B");
    ui.lineEdit_31->setText(str[0]);
    ui.lineEdit_31->setInputMask("B");

    updateInfo();
}

void DeviceVS::updateInfo()
{

    //ОБНОВЛЕНИЕ ИНФОРМАЦИИ О ГРУППЕ РЕГИСТРОВ ДВА
    //Reg0[D3:D0]
    switch (m_reg[0] & 0xF)
    {
    case(0):
        ui.label_2->setText("Не задан");
        break;
    case(1):
        ui.label_2->setText("Тестирование");
        break;
    case(2):
        ui.label_2->setText("Молчание");
        break;
    case(3):
        ui.label_2->setText("Основной");
        break;
    }

    //Reg0[D7:D4]
    switch (m_reg[0] >> 4)
    {
    case(0):
        ui.label_4->setText("Не задан");
        break;
    case(1):
        ui.label_4->setText("Симплексная");
        break;
    case(2):
        ui.label_4->setText("Дуплексная");
        break;
    case(3):
        ui.label_4->setText("Полудуплексная");
        break;
    }

    //Reg1
    switch (m_reg[1])
    {
    case(0):
        ui.label_9->setText("Не задана");
        break;
    case(1):
        ui.label_9->setText("2,4");
        break;
    case(2):
        ui.label_9->setText("4,8");
        break;
    case(3):
        ui.label_9->setText("9,6");
        break;
    case(0x11):
        ui.label_9->setText("32");
        break;
    case(0x12):
        ui.label_9->setText("64");
        break;
    case(0x13):
        ui.label_9->setText("128");
        break;
    case(0x14):
        ui.label_9->setText("256");
        break;
    case(0x15):
        ui.label_9->setText("512");
        break;

    }

    //Reg7[D0]
    if(m_reg[7] & 1)
        ui.label_16->setText("Инверсия есть");
    else
        ui.label_16->setText("Инверсии нет");

    //Reg7[D4]    
    if (m_reg[7] & 0x10)
        ui.label_19->setText("Сжатие есть");
    else
        ui.label_19->setText("Сжатия нет");

    //ОБНОВЛЕНИЕ ИНФОРМАЦИИ О ГРУППЕ РЕГИСТРОВ ДВА
    //------------------Абонент 1--------------------------------------------------
    if (m_reg[10] & 1)
        ui.label_22->setText("Автовызов, Да");
    else
        ui.label_22->setText("Автовызов, Нет");

    if (m_reg[10] & 2)
        ui.label_24->setText("Поддежка связи, Да");
    else
        ui.label_24->setText("Поддежка связи, Нет");
    //=============================================================================	
    //------------------Абонент 2--------------------------------------------------
    if (m_reg[13] & 1)
        ui.label_31->setText("Автовызов, Да");
    else
        ui.label_31->setText("Автовызов, Нет");

    if (m_reg[13] & 2)
        ui.label_33->setText("Поддежка связи, Да");
    else
        ui.label_33->setText("Поддежка связи, Нет");
    //=============================================================================

    //------------------Абонент 3--------------------------------------------------
    if (m_reg[16] & 1)
        ui.label_40->setText("Автовызов, Да");
    else
        ui.label_40->setText("Автовызов, Нет");

    if (m_reg[16] & 2)
        ui.label_42->setText("Поддежка связи, Да");
    else
        ui.label_42->setText("Поддежка связи, Нет");
    //=============================================================================

    //------------------Абонент 4--------------------------------------------------
    if (m_reg[19] & 1)
        ui.label_49->setText("Автовызов, Да");
    else
        ui.label_49->setText("Автовызов, Нет");

    if (m_reg[19] & 2)
        ui.label_51->setText("Поддежка связи, Да");
    else
        ui.label_51->setText("Поддежка связи, Нет");
    //=============================================================================
    
    //ОБНОВЛЕНИЕ ИНФОРМАЦИИ О ГРУППЕ РЕГИСТРОВ ДВА
        //РГ32[D0]
    if (m_reg[32] & 1)
    {
        ui.label_55->setText("Модем исправен");
        ui.label_55->setStyleSheet("QLabel { background-color : green; color : black; }");
    }
    else
    {
        ui.label_55->setText("Модем не исправен");
        ui.label_55->setStyleSheet("QLabel { background-color : red; color : black; }");
    }

    //РГ32[D2:D1]
    char twoBit = (m_reg[32] >> 1) & 3;

    switch (twoBit)
    {
    case(0):
        ui.label_57->setText("Сигнал: Норма");
        ui.label_57->setStyleSheet("QLabel { background-color : green; color : black; }");
        break;
    case(1):
        ui.label_57->setText("Сигнал: Предупреждение");
        ui.label_57->setStyleSheet("QLabel { background-color : yellow; color : black; }");
        break;
    case(2):
        ui.label_57->setText("Сигнал: Ошибка");
        ui.label_57->setStyleSheet("QLabel { background-color : red; color : black; }");
    }

    //РГ32[D4:D3]
    twoBit = (m_reg[32] >> 3) & 3;

    switch (twoBit)
    {
    case(0):
        ui.label_59->setText("Связь: Норма");
        ui.label_59->setStyleSheet("QLabel { background-color : green; color : black; }");
        break;
    case(1):
        ui.label_59->setText("Связь: Предупреждение");
        ui.label_59->setStyleSheet("QLabel { background-color : yellow; color : black; }");
        break;
    case(2):
        ui.label_59->setText("Связь: Ошибка");
        ui.label_59->setStyleSheet("QLabel { background-color : red; color : black; }");
    }

    //РГ32[D5]
    if (m_reg[32] >> 5)
    {
        ui.label_61->setText("Наличие информации: Есть");
        ui.label_61->setStyleSheet("QLabel { background-color : green; color : black; }");
    }
    else
    {
        ui.label_61->setText("Наличие информации: Нет");
        ui.label_61->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    }

    //РГ33
    if (m_reg[33] >= 170)
        ui.label_62->setStyleSheet("QLabel { background-color : green; color : black; }");
    else if (m_reg[33] >= 85)
        ui.label_62->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    else
        ui.label_62->setStyleSheet("QLabel { background-color : red; color : black; }");

    std::bitset<4> rg34(m_reg[34]);
    //РГ34[D0]
    if (rg34[0])
    {
        ui.label_65->setText("Связь с абонентом №1: Есть");
        ui.label_65->setStyleSheet("QLabel { background-color : green; color : black; }");
    }
    else
    {
        ui.label_65->setText("Связь с абонентом №1: Нет");
        ui.label_65->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    }


    //РГ34[D1]
    if (rg34[1])
    {
        ui.label_67->setText("Связь с абонентом №2: Есть");
        ui.label_67->setStyleSheet("QLabel { background-color : green; color : black; }");
    }
    else
    {
        ui.label_67->setText("Связь с абонентом №2: Нет");
        ui.label_67->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    }


    //РГ34[D2]
    if (rg34[2])
    {
        ui.label_71->setText("Связь с абонентом №3: Есть");
        ui.label_71->setStyleSheet("QLabel { background-color : green; color : black; }");
    }
    else
    {
        ui.label_71->setText("Связь с абонентом №3: Нет");
        ui.label_71->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    }


    //РГ34[D3]
    if (rg34[3])
    {
        ui.label_72->setText("Связь с абонентом №4: Есть");
        ui.label_72->setStyleSheet("QLabel { background-color : green; color : black; }");
    }
    else
    {
        ui.label_72->setText("Связь с абонентом №4: Нет");
        ui.label_72->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    }
}

char DeviceVS::binaryStringToInt(QString str)
{
    char res = 0;
    for (auto& i : str)
    {
        res <<= 1;
        res += i.unicode() - '0';
    }
    return res;
}
