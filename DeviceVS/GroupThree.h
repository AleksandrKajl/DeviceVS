#pragma once
#include"ui_GroupThree.h"

class GroupThree : public QMainWindow
{
	Q_OBJECT
public:
	GroupThree(QWidget* parent = nullptr);

private:
	Ui::MainWindow ui;

	std::array<char, 12> reg{ 0 };

private slots:
	void slotEditReg0();

private:
	void initReg();

	void updateInfo();


};