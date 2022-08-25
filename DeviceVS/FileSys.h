#pragma once
#include<QMainWindow>
#include<QDir>

//Класс для логирования и работы с файловой системой
class FileSys : public QMainWindow
{
public:
	FileSys(QWidget* parent = nullptr);
	~FileSys();

	QString readLog();
	void saveSettings(QByteArray& data);
	QByteArray loadSettings();
	void writeLog(const QString& reqType, const uint8_t group, const QByteArray& data);
private:
	QString dataToStr(const QByteArray& data);

private:
	QFile* file;
	const QString logFileName = "logfile.log";
};