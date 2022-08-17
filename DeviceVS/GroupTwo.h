#pragma once
#include"ui_GroupTwo.h"

class GroupTwo : public QMainWindow
{
	Q_OBJECT
public:
	GroupTwo(QWidget* parent = nullptr);
	
private:
	Ui::MainWindow ui;

	std::array<char, 12> reg{0};

private slots:
	void slotEditReg0();
	void slotEditReg1();
	void slotEditReg2();
	void slotEditReg3();

private:
	void initReg();

	void updateInfo();


};