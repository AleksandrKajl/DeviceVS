#pragma once
#include<QMainWindow>
#include<QDir>

class FileSys : public QMainWindow
{
public:
	FileSys(QWidget* parent = nullptr);
	~FileSys();

	QString openLog();
	void saveSettings(QByteArray& data);
	QByteArray loadSettings();
	QFile* getFile();
	void writeLog(const QString& str, uint8_t group, const QByteArray& data);
private:
	QString dataToStr(const QByteArray& data);

private:
	QFile* file;
	const QString logFileName = "logfile.log";
};