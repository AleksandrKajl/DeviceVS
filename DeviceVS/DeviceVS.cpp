#include "DeviceVS.h"
#include"GroupTwo.h"
#include"GroupThree.h"
#include<QMessageBox>

DeviceVS::DeviceVS(QWidget* parent)
    : QMainWindow(parent)
    , m_pUdpSock(new QUdpSocket(this))
    , m_pGroupTwo(nullptr)
    , m_pGroupThree(nullptr)
    , m_pValidRG5(new QIntValidator(0, 30000, this))
    , m_fs(new FileSys(this))
    , m_txtEdt(new QTextEdit())
{

    m_reg.fill(0, 40);
    ui.setupUi(this);
    m_pGroupTwo = new GroupTwo(this);
    m_pGroupThree = new GroupThree(this);

    m_pUdpSock->bind(5555);
    
    //ui.mainToolBar->addAction(QIcon(":/Resource/open-file.png"), tr("Open"), this, SLOT(openFile()));
    connect(ui.action, SIGNAL(triggered()), SLOT(slotOpenLog()));
    connect(ui.action_2, SIGNAL(triggered()), SLOT(slotLoadSettings()));
    connect(ui.action_3, SIGNAL(triggered()), SLOT(slotSaveSettings()));
    connect(m_pUdpSock, SIGNAL(readyRead()), SLOT(slotRecievRequest()));
    //ГРУППА РЕГИСТРОВ ОДИН
    connect(ui.lineEdit, SIGNAL(editingFinished()), SLOT(slotEditReg0L()));
    connect(ui.lineEdit_2, SIGNAL(editingFinished()), SLOT(slotEditReg0H()));
    connect(ui.lineEdit_3, SIGNAL(editingFinished()), SLOT(slotEditReg1()));
    connect(ui.lineEdit_4, SIGNAL(editingFinished()), SLOT(slotEditReg5Reg6()));
    connect(ui.lineEdit_5, SIGNAL(editingFinished()), SLOT(slotEditReg7_0()));
    connect(ui.lineEdit_6, SIGNAL(editingFinished()), SLOT(slotEditReg7_4()));

    ui.lineEdit_4->setValidator(m_pValidRG5);
    //m_reg[0] = 33;
    //m_reg[1] = 0x15;
    ////Reg2 -Reg4 reserve
    //m_reg[5] = 0x75;
    //m_reg[6] = 0x30;
    //m_reg[7] = 0X11;
    initReg();
}

DeviceVS::~DeviceVS()
{
    delete m_txtEdt;
}

DeviceVS* DeviceVS::getPtr()
{
    return this;
}

//Приём запроса
void DeviceVS::slotRecievRequest()
{
    QByteArray data;
    do
    {
        data.resize(m_pUdpSock->pendingDatagramSize());
        m_pUdpSock->readDatagram(data.data(), data.size());
    } while (m_pUdpSock->hasPendingDatagrams());

    QDataStream in(&data, QIODevice::ReadOnly);
    uint8_t request{};
    uint8_t groupReg{};
    in >> request >> groupReg;
    if (request == READ_REQ)
    {
        m_pUdpSock->writeDatagram(readData(groupReg), QHostAddress::LocalHost, 4444);
    }
    else if(request == WRITE_REQ)
    {
        QByteArray reg;
        in >> reg;
        writeData(reg, groupReg);
        //m_pUdpSock->writeDatagram(writeData(reg, groupReg), QHostAddress::LocalHost, 4444);
    }
    else
        QMessageBox::warning(this, "Предупреждение", "Принят ошибочный запрос!");

}

//Запись принятых данных в массив регистров
QByteArray DeviceVS::writeData(QByteArray& reg, const uint8_t groupReg)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    switch (groupReg)
    {
    case(0):
        m_reg.replace(0, 40, reg);
        initAllReg();
        break;
    case(1):
        m_reg.replace(0, 8, reg);
        initReg();
        break;
    case(2):
        m_reg.replace(8, 23, reg);
        m_pGroupTwo->initReg();
        break;
    case(3):
        m_reg.replace(32, 8, reg);
        m_pGroupThree->initReg();
        break;
    default:
        QMessageBox::warning(this, "Предупреждение", "Заппись в эту группу регистров не возможна, её не существует!");

    }
    
    QString str = "Запись данных\t";
    m_fs->writeLog(str, groupReg ,reg);
    out << REQ_COMPLETED << REG_GROUP_1;
    return data;

}

void DeviceVS::initAllReg()
{
    initReg();
    m_pGroupTwo->initReg();
    m_pGroupThree->initReg();
}

//Чтение данных для отправки
QByteArray DeviceVS::readData(const uint8_t groupReg)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);    
    QString str = "Чтение данных\t";

    switch (groupReg)
    {
    case(0):
        m_fs->writeLog(str, REG_ALL, m_reg);
        out << REQ_COMPLETED << REG_ALL << m_reg;
        break;
    case(1):
        m_fs->writeLog(str, REG_GROUP_1 , m_reg.sliced(0, 8));
        out << REQ_COMPLETED << REG_GROUP_1 << m_reg.sliced(0, 8);
        break;
    case(2):
        m_fs->writeLog(str, REG_GROUP_2 , m_reg.sliced(8, 23));
        out << REQ_COMPLETED << REG_GROUP_2 << m_reg.sliced(8, 23);
        break;
    case(3):
        m_fs->writeLog(str, REG_GROUP_3 , m_reg.sliced(32, 8));
        out << REQ_COMPLETED << REG_GROUP_3 << m_reg.sliced(32, 8);
    }

    return data;
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
    QString str("0x" + ui.lineEdit_3->text());
    bool Ok{};
    m_reg[1] = str.sliced(2).toInt(&Ok, 16);
    if (!Ok)
        return;
    updateInfo();
}

void DeviceVS::slotEditReg5Reg6()
{
    char16_t var = ui.lineEdit_4->text().toInt();
    m_reg[5] = var & 0xFF;
    m_reg[6] = var >> 8;
}

void DeviceVS::slotOpenLog()
{
    m_txtEdt->resize(1150, 800);
    m_txtEdt->setWindowTitle("Журнал событий");
    m_txtEdt->show();
    m_txtEdt->setPlainText(m_fs->openLog());
    m_txtEdt->setReadOnly(true);
}

void DeviceVS::slotSaveSettings()
{
    m_fs->saveSettings(m_reg);
}

void DeviceVS::slotLoadSettings()
{
    QByteArray data;
    data = m_fs->loadSettings();
    if (data.isEmpty())
        return;
    else if (data.size() == 40)
    {
        m_reg.replace(0, 40, data);
        initAllReg();
    }
    else
        QMessageBox::warning(this, "Не возможго загрузить настройки",
            "Настройки не соответствуют требованиям");

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
    ui.lineEdit_3->setText(QString::number(m_reg[1], 16));
    ui.lineEdit_3->setInputMask("hh");

    //Reg2 -Reg4 reserve
    //Reg5 - Reg6
    ui.lineEdit_4->setText(QString::number((uint16_t)((m_reg[6] * 0x100) + m_reg[5])));      //Собираем значение из двух байт
    //ui.lineEdit_4->setInputMask("99999");
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

