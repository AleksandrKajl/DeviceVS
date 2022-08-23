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

private:
	QFile* file;
};