#pragma once
#include "DeviceVS.h"
#include <QFile>

class MyInfo : public QMainWindow
{
public:
	MyInfo(QWidget* parent = nullptr);
	~MyInfo();

private:
	QTextEdit* m_pInfo;
	QFile* file;

private:
	void loadInfo();
};