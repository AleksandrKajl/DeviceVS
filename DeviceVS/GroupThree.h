#pragma once
#include"ui_GroupThree.h"

class GroupThree : public QMainWindow
{
	Q_OBJECT
public:
	GroupThree(QWidget* parent = nullptr);

private:
	Ui::GroupTree ui;

	std::array<unsigned char, 8> reg{ 0 };

private slots:
	void slotEditLine();
	void slotEditLine_2();
	void slotEditLine_3();
	void slotEditLine_4();
	void slotEditLine_5();
	void slotEditLine_6();
	void slotEditLine_7();
	void slotEditLine_8();
	void slotEditLine_9();

private:
	void initReg();
	void updateInfo();

};