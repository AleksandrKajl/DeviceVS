#include"FileSys.h"
#include<QFileDialog>

FileSys::FileSys(QWidget* parent)
    : QMainWindow(parent)
    , file(new QFile())
{
}

FileSys::~FileSys()
{
    delete file;
}

//Метод преобразованния данных в строку hex данных вида (FF 00 6A)
QString FileSys::dataToStr(const QByteArray& data)
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
void FileSys::writeLog(const QString& reqType, const uint8_t group, const QByteArray& data)
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
QString FileSys::readLog()
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
void FileSys::saveSettings(QByteArray& data)
{
    QString str = QFileDialog::getSaveFileName(this, tr("Save settings"),
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
QByteArray FileSys::loadSettings()
{
    QString str = QFileDialog::getOpenFileName(this, tr("Load settings"),
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