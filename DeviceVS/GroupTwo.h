#pragma once
#include"ui_GroupTwo.h"

class GroupTwo : public QMainWindow
{
	Q_OBJECT
public:
	GroupTwo(QWidget* parent = nullptr);
	
private:
	Ui::MainWindow ui;

	std::array<char, 23> reg{0};

private slots:
	void slotEditReg0();
	void slotEditReg1();
	void slotEditReg2();
	void slotEditReg3();

	void slotEditReg4();
	void slotEditReg5();
	void slotEditReg6();
	void slotEditReg7();

	void slotEditReg8();
	void slotEditReg9();
	void slotEditReg10();
	void slotEditReg11();

	void slotEditReg12();
	void slotEditReg13();
	void slotEditReg14();
	void slotEditReg15();


private:
	void initReg();

	void updateInfo();


};