#pragma once
#include<QMainWindow>
#include<QDir>

class FileSys : public QMainWindow
{
public:
	FileSys(QWidget* parent = nullptr);
	~FileSys();

	QString openFile();
	void saveFile(QString txt);
	QString loadFile(QString str);
	QFile* getFile();
	void writeLog(QString str, uint8_t group,QByteArray data);
private:
	QString dataToStr(QByteArray& data);

private:
	QFile* file;
};