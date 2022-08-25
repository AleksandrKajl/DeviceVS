#include"MyLog.h"
#include<QFileDialog>

MyLog::MyLog(QWidget* parent)
    : QMainWindow(parent)
    , file(new QFile())
{
}

MyLog::~MyLog()
{
    delete file;
}

//Метод преобразованния данных в строку hex данных вида (FF 00 6A)
QString MyLog::dataToStr(const QByteArray& data)
{
    QString str;
    for (int i{}; i < data.size(); ++i)
    {
        QString prefix;
        if ((uint8_t)data[i] < 0x10)
            prefix.append("0");         //Добавляем впереди 0 если значение состоит из одной hex цифры
        str.append(prefix + QString::number((uint8_t)data[i], 16).toUpper() + ' ');
    }
    return str;
}

//Метод ля записи данных в log файл 
void MyLog::writeLog(const QString& reqType, const uint8_t group, const QByteArray& data)
{
    QString txt;
    file->setFileName(logFileName);
    if (file->open(QFile::ReadOnly | QFile::ExistingOnly))
    {
        txt = file->readAll();
        file->close();
    }

    if (file->open(QFile::WriteOnly))
    {
        QTextStream log(file);
        log << txt <<QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss\t")
            << reqType << "Группа регистров " << group <<'\t' 
            << dataToStr(data) << '\n';
        file->close();
    }
}

//Метод для чтения лога из файла
QString MyLog::readLog()
{
    file->setFileName(logFileName);
    if (file->open(QFile::ReadOnly))
    {
        QString text;
        QTextStream stream(file);       
        text = stream.readAll();
        file->close();
        return text;
    }

    return nullptr;
}

//Метод сохранения настроек устройства
void MyLog::saveSettings(QByteArray& data)
{
    QString str = QFileDialog::getSaveFileName(this, "Сохранить настройки",
        QDir::currentPath(), tr("All(*.*)"));

    if (!str.isEmpty())
    {
        file->setFileName(str);
        if (file->open(QFile::WriteOnly))
        {
            QDataStream stream(file);
            stream << data;
            file->close();
        }
    }
}

//Загрузка настроек устройства
QByteArray MyLog::loadSettings()
{
    QString str = QFileDialog::getOpenFileName(this, "Загрузить настройки",
        QDir::currentPath(), tr("All(*.*)"));

    file->setFileName(str);
    if (file->open(QFile::ReadOnly | QFile::Text))
    {
        QByteArray data;
        QDataStream in(file);
        in >> data;       
        file->close();
        return data;
    }

    return nullptr;
}