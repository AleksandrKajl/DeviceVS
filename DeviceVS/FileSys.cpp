#include"FileSys.h"
#include<QFileDialog>

FileSys::FileSys(QWidget* parent)
    : QMainWindow(parent)
    , file(new QFile("logfile.txt"))
{
    
}

FileSys::~FileSys()
{
    delete file;
}

QString FileSys::dataToStr(QByteArray& data)
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

void FileSys::writeLog(QString str,uint8_t group, QByteArray data)
{
    QString txt;
    file->setFileName("logfile.txt");
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

QString FileSys::openFile()
{
    file->setFileName("logfile.txt");
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

void FileSys::saveFile(QString txt)
{
    QString str = QFileDialog::getSaveFileName(this, tr("Save file"),
        QDir::currentPath(), tr("Text file(*.txt);; All(*.*)"));

    if (!str.isEmpty())
    {
        if (str.endsWith(".txt"))
        {
            file->setFileName(str);
            if (file->open(QFile::WriteOnly))
            {
                QTextStream stream(file);
                stream << txt;
            }
        }
    }
}

QString FileSys::loadFile(QString str)
{
    file->setFileName(str);
    if (file->open(QFile::ReadOnly | QFile::ExistingOnly))
        str = file->readAll();

    return str;
}

QFile* FileSys::getFile()
{
    return file;
}
