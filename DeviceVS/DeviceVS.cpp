#include"DeviceVS.h"
#include"GroupTwo.h"
#include"GroupThree.h"
#include"FileSys.h"

DeviceVS::DeviceVS(QWidget* parent)
    : QMainWindow(parent)
    , m_pUdpSock(new QUdpSocket(this))
    , m_pGroupTwo(nullptr)
    , m_pGroupThree(nullptr)
    , m_pValidRG5(new QIntValidator(0, 99999, this))    //Валидатор для РГ5-РГ6
    , m_pFs(new FileSys(this))
    , m_txtEdt(new QTextEdit())
{
    ui.setupUi(this);
    m_reg.fill(0, 40);
    m_pGroupTwo = new GroupTwo(this);
    m_pGroupThree = new GroupThree(this);
    
    // Привязываем сокет к адресу LocalHost и порту для получения данных от клиента 
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

    initReg();
}

DeviceVS::~DeviceVS()
{
    delete m_txtEdt;
}

//Приём запроса на проведения операции
void DeviceVS::slotRecievRequest()
{
    if(!data.isEmpty())
        data.clear();

    do
    {
        data.resize(m_pUdpSock->pendingDatagramSize());
        m_pUdpSock->readDatagram(data.data(), data.size());
    } while (m_pUdpSock->hasPendingDatagrams());

    QDataStream in(&data, QIODevice::ReadOnly);
    uint8_t request{};
    uint8_t groupReg{};
    in >> request >> groupReg;

    //Определяем тип запроса
    if (request == READ_REQ)
    {
        //Отправляем прочитанные регистры
        m_pUdpSock->writeDatagram(readData(groupReg), QHostAddress::LocalHost, PORT_WRITE);
    }
    else if(request == WRITE_REQ)
    {
        QByteArray reg;
        in >> reg;
        //Записываем полученные данные
        writeData(reg, groupReg);
        //m_pUdpSock->writeDatagram(writeData(reg, groupReg), QHostAddress::LocalHost, 4444);
    }
    else
        QMessageBox::warning(this, "Ошибка запроса", "Принят ошибочный запрос!");
}

//Чтение данных для отправки
QByteArray DeviceVS::readData(const uint8_t groupReg)
{
    if (!data.isEmpty())
        data.clear();

    QDataStream out(&data, QIODevice::WriteOnly);
    QString str = "Чтение данных\t";

    switch (groupReg)
    {
    case 0:
        m_pFs->writeLog(str, REG_ALL, m_reg);
        out << REQ_COMPLETED << REG_ALL << m_reg;
        break;
    case 1:
        m_pFs->writeLog(str, REG_GROUP_1, m_reg.sliced(0, 8));
        out << REQ_COMPLETED << REG_GROUP_1 << m_reg.sliced(0, 8);
        break;
    case 2:
        m_pFs->writeLog(str, REG_GROUP_2, m_reg.sliced(8, 23));
        out << REQ_COMPLETED << REG_GROUP_2 << m_reg.sliced(8, 23);
        break;
    case 3:
        m_pFs->writeLog(str, REG_GROUP_3, m_reg.sliced(32, 8));
        out << REQ_COMPLETED << REG_GROUP_3 << m_reg.sliced(32, 8);
        break;
    default:
        m_pFs->writeLog("Ошибка чтения данных\t", groupReg, nullptr);
        out << REQ_FAILED << groupReg;
        QMessageBox::warning(this, "Ошибка отправки ответа", "Такой группы регистров не существует");
    }

    return data;
}

//Запись принятых данных в массив регистров
QByteArray DeviceVS::writeData(QByteArray& reg, const uint8_t groupReg)
{
    if (!data.isEmpty())
        data.clear();

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
        m_pFs->writeLog("Ошибка записи данных\t", groupReg, reg);
        out << REQ_FAILED << groupReg;
        QMessageBox::warning(this, "Ошибка записи", "Заппись в не существующую группу регистров");
        return data;
    }
    
    m_pFs->writeLog("Запись данных\t", groupReg ,reg);
    out << REQ_COMPLETED << groupReg;
    return data;
}

//Инициализация всех групп регистров
void DeviceVS::initAllReg()
{
    initReg();
    m_pGroupTwo->initReg();
    m_pGroupThree->initReg();
}

//ГРУППА РЕГИСТРОВ 1
void DeviceVS::slotEditReg0L()
{
    //Используем маску, чтобы не затронуть старший полубайт
    m_reg[0] = (m_reg[0] & 0xF0) + binaryStringToInt(ui.lineEdit->text());
    updateInfo();
}

void DeviceVS::slotEditReg0H()
{
    ////Используем маску, чтобы не затронуть младший полубайт
    m_reg[0] = (m_reg[0] & 0xF) + ((binaryStringToInt(ui.lineEdit_2->text()) << 4));
    updateInfo();
}

void DeviceVS::slotEditReg1()
{
    bool Ok{};
    m_reg[1] = ui.lineEdit_3->text().toInt(&Ok, 16);
    if (!Ok)
        return;
    updateInfo();
}

void DeviceVS::slotEditReg5Reg6()
{
    uint16_t var = ui.lineEdit_4->text().toInt();
    m_reg[5] = var & 0xFF;          
    m_reg[6] = var >> 8;
    updateInfo();
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

//Слот для вывода журнала событий в приложении
void DeviceVS::slotOpenLog()
{
    m_txtEdt->resize(1150, 800);
    m_txtEdt->setWindowTitle("Журнал событий");
    m_txtEdt->show();
    m_txtEdt->setPlainText(m_pFs->readLog());
    m_txtEdt->setReadOnly(true);
}

void DeviceVS::slotSaveSettings()
{
    m_pFs->saveSettings(m_reg);
}

//Загрузка настроек устройства из данных не 40 байт, то ошибка, настройки не загруженны
void DeviceVS::slotLoadSettings()
{
    if (!data.isEmpty())
        data.clear();

    data = m_pFs->loadSettings();
    if (data.isEmpty())
        return;
    else if (data.size() == 40)
    {
        m_reg.replace(0, 40, data);
        initAllReg();
    }
    else
        QMessageBox::warning(this, "Не возможно загрузить настройки",
            "Настройки не соответствуют требованиям");
}

//Установка полей приложения в соответствии регистрам устройства
void DeviceVS::initReg()
{
    //ИНИЦИАЛИЗАЦИЯ ГРУППЫ РЕГИСТРОВ ОДИН
    //Reg0
    //Порядок бит в строке перевернут
    QString binStr = QString::fromStdString(std::bitset<8>(m_reg[0]).to_string());
    ui.lineEdit->setText(binStr.sliced(4, 4));
    ui.lineEdit->setInputMask("bbbb");
    ui.lineEdit_2->setText(binStr.sliced(0, 4));
    ui.lineEdit_2->setInputMask("bbbb");
    //Reg1
    ui.lineEdit_3->setText(QString::number((uint8_t)m_reg[1], 16));
    ui.lineEdit_3->setInputMask("hh");
    //Reg2 -Reg4 reserve
    //Reg5 - Reg6
    ui.lineEdit_4->setValidator(m_pValidRG5);
    ui.lineEdit_4->setText(QString::number((uint16_t)((m_reg[6] * 0x100) + m_reg[5])));      //Собираем значение из двух байт
    binStr = QString::fromStdString(std::bitset<8>(m_reg[7]).to_string());
    ui.lineEdit_5->setText(binStr[7]);
    ui.lineEdit_5->setInputMask("B");
    ui.lineEdit_6->setText(binStr[3]);
    ui.lineEdit_6->setInputMask("B");

    updateInfo();
}

//Обновляем видимую информацию о регистрах
void DeviceVS::updateInfo()
{
    //ОБНОВЛЕНИЕ ИНФОРМАЦИИ О ГРУППЕ РЕГИСТРОВ ОДИН
    //Reg0[D3:D0]
    QString err("Не верное значение");
    switch (m_reg[0] & 0xF)
    {
    case 0:
        ui.label_2->setText("Не задан");
        break;
    case 1:
        ui.label_2->setText("Тестирование");
        break;
    case 2:
        ui.label_2->setText("Молчание");
        break;
    case 3:
        ui.label_2->setText("Основной");
        break;
    default:
        ui.label_2->setText(err);
    }

    //Reg0[D7:D4]
    switch (m_reg[0] >> 4)
    {
    case 0:
        ui.label_4->setText("Не задан");
        break;
    case 1:
        ui.label_4->setText("Симплексная");
        break;
    case 2:
        ui.label_4->setText("Дуплексная");
        break;
    case 3:
        ui.label_4->setText("Полудуплексная");
        break;
    default:
        ui.label_4->setText(err);
    }

    //Reg1
    switch (m_reg[1])
    {
    case 0:
        ui.label_9->setText("Не задана");
        break;
    case 1:
        ui.label_9->setText("2,4");
        break;
    case 2:
        ui.label_9->setText("4,8");
        break;
    case 3:
        ui.label_9->setText("9,6");
        break;
    case 0x11:
        ui.label_9->setText("32");
        break;
    case 0x12:
        ui.label_9->setText("64");
        break;
    case 0x13:
        ui.label_9->setText("128");
        break;
    case 0x14:
        ui.label_9->setText("256");
        break;
    case 0x15:
        ui.label_9->setText("512");
        break;
    default:
        ui.label_9->setText(err);
    }

    //Reg5-Reg6
    if ((m_reg[5] + (m_reg[6] << 8)) > 30000)
        ui.label_12->setText(err);
    else
        ui.label_12->setText("Частота(МГц)");
        
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

//Метод перевода двоичной строки в целое число
char DeviceVS::binaryStringToInt(const QString& str)
{
    uint8_t res = 0;
    for (auto& i : str)
    {
        res <<= 1;
        res += i.unicode() - '0';
    }
    return res;
}

