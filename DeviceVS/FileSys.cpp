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

QString FileSys::dataToStr(const QByteArray& data)
{
    QString str;
    for (int i{}; i < data.size(); ++i)
    {
        QString prefix;
        if ((uint8_t)data[i] < 0x10)
            prefix.append("0");
        str.append(prefix + QString::number((uint8_t)data[i], 16).toUpper() + ' ');
    }
    return str;
}

void FileSys::writeLog(const QString& str, uint8_t group, const QByteArray& data)
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
            << str << "Группа регистров " << group <<'\t' 
            << dataToStr(data) << '\n';
        file->close();
    }
}

QString FileSys::openLog()
{
    file->setFileName(logFileName);
    if (file->open(QFile::ReadOnly | QFile::Text))
    {
        QString text;
        QTextStream stream(file);       
        text = stream.readAll();
        file->close();
        return text;
    }

    return nullptr;
}

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

QFile* FileSys::getFile()
{
    return file;
}
