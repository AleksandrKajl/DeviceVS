#include "DeviceVS.h"
#include"GroupTwo.h"
#include"GroupThree.h"

DeviceVS::DeviceVS(QWidget* parent)
    : QMainWindow(parent)
    , m_udpSock(new QUdpSocket(this))
    , m_pGroupTwo(nullptr)
    , m_pGroupThree(nullptr)
{
    ui.setupUi(this);
    m_pGroupTwo = new GroupTwo(this);
    m_pGroupThree = new GroupThree(this);
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
