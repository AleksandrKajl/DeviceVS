#include "Info.h"

MyInfo::MyInfo(QWidget* parent)
	: QMainWindow(parent)
	, m_pInfo(new QTextEdit())
	, file(new QFile())
{
	setWindowTitle("Info");
	setWindowIcon(QIcon(":/DeviceVS/Resource/info.png"));
	setCentralWidget(m_pInfo);
	m_pInfo->setReadOnly(true);
	setWindowModality(Qt::ApplicationModal);
	QPalette pal = m_pInfo->palette();
	pal.setColor(QPalette::Base, QColor(240,240,240));
	m_pInfo->setPalette(pal);
	loadInfo();
}

MyInfo::~MyInfo()
{
	delete file;
}

void MyInfo::loadInfo()
{
    //QString txt;
    file->setFileName(":/DeviceVS/Resource/info.txt");
    if (file->open(QFile::ReadOnly | QFile::ExistingOnly))
    {
        //txt = file->readAll();
		m_pInfo->setText(file->readAll());
        file->close();
    }
}

