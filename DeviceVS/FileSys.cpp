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
