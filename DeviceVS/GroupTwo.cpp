#include"GroupTwo.h"
#include<bitset>

GroupTwo::GroupTwo(QWidget* parent) 
	: QMainWindow(parent)
{
	ui.setupUi(this);

	reg[0] = 77;
	reg[1] = 3;
	reg[2] = 3;	//reg3[D:0] и reg4[D1]
	//----------------Абонент 1-------------------------------------------------------------
	connect(ui.lineEdit, SIGNAL(editingFinished()), SLOT(slotEditReg0()));
	connect(ui.lineEdit_2, SIGNAL(editingFinished()), SLOT(slotEditReg1()));
	connect(ui.lineEdit_3, SIGNAL(editingFinished()), SLOT(slotEditReg2()));
	connect(ui.lineEdit_4, SIGNAL(editingFinished()), SLOT(slotEditReg3()));
	//======================================================================================
	//----------------Абонент 2-------------------------------------------------------------
	connect(ui.lineEdit_5, SIGNAL(editingFinished()), SLOT(slotEditReg4()));
	connect(ui.lineEdit_6, SIGNAL(editingFinished()), SLOT(slotEditReg5()));
	connect(ui.lineEdit_7, SIGNAL(editingFinished()), SLOT(slotEditReg6()));
	connect(ui.lineEdit_8, SIGNAL(editingFinished()), SLOT(slotEditReg7()));
	//======================================================================================
	//----------------Абонент 3-------------------------------------------------------------
	connect(ui.lineEdit_9, SIGNAL(editingFinished()), SLOT(slotEditReg8()));
	connect(ui.lineEdit_19, SIGNAL(editingFinished()), SLOT(slotEditReg9()));
	connect(ui.lineEdit_20, SIGNAL(editingFinished()), SLOT(slotEditReg10()));
	connect(ui.lineEdit_21, SIGNAL(editingFinished()), SLOT(slotEditReg11()));
	//======================================================================================
	//----------------Абонент 4-------------------------------------------------------------
	connect(ui.lineEdit_22, SIGNAL(editingFinished()), SLOT(slotEditReg12()));
	connect(ui.lineEdit_23, SIGNAL(editingFinished()), SLOT(slotEditReg13()));
	connect(ui.lineEdit_24, SIGNAL(editingFinished()), SLOT(slotEditReg14()));
	connect(ui.lineEdit_25, SIGNAL(editingFinished()), SLOT(slotEditReg15()));
	//======================================================================================

	initReg();
	

}
//------------------Абонент 1----------------------
void GroupTwo::slotEditReg0()
{
	reg[0] = ui.lineEdit->text().toInt();
}

void GroupTwo::slotEditReg1()
{
	reg[1] = ui.lineEdit_2->text().toInt();
}

void GroupTwo::slotEditReg2()
{
	std::bitset<2> b(reg[2]);
	b[0] = ui.lineEdit_3->text().toInt();
	reg[2] = b.to_ulong();

	updateInfo();
}

void GroupTwo::slotEditReg3()
{
	std::bitset<2> b(reg[2]);
	b[1] = ui.lineEdit_4->text().toInt();
	reg[2] = b.to_ulong();

	updateInfo();
}
//==================================================
//----------------Абонент 2-------------------------
void GroupTwo::slotEditReg4()
{
	reg[3] = ui.lineEdit_5->text().toInt();
}

void GroupTwo::slotEditReg5()
{
	reg[4] = ui.lineEdit_6->text().toInt();
}

void GroupTwo::slotEditReg6()
{
	std::bitset<2> b(reg[5]);
	b[0] = ui.lineEdit_7->text().toInt();
	reg[5] = b.to_ulong();

	updateInfo();
}

void GroupTwo::slotEditReg7()
{
	std::bitset<2> b(reg[5]);
	b[1] = ui.lineEdit_8->text().toInt();
	reg[5] = b.to_ulong();

	updateInfo();
}

//==================================================
//----------------Абонент 3-------------------------
void GroupTwo::slotEditReg8()
{
	reg[6] = ui.lineEdit_9->text().toInt();
}

void GroupTwo::slotEditReg9()
{
	reg[7] = ui.lineEdit_19->text().toInt();
}

void GroupTwo::slotEditReg10()
{
	std::bitset<2> b(reg[8]);
	b[0] = ui.lineEdit_20->text().toInt();
	reg[8] = b.to_ulong();

	updateInfo();
}

void GroupTwo::slotEditReg11()
{
	std::bitset<2> b(reg[8]);
	b[1] = ui.lineEdit_21->text().toInt();
	reg[8] = b.to_ulong();

	updateInfo();
}

//==================================================
//----------------Абонент 4-------------------------
void GroupTwo::slotEditReg12()
{
	reg[9] = ui.lineEdit_22->text().toInt();
}

void GroupTwo::slotEditReg13()
{
	reg[10] = ui.lineEdit_23->text().toInt();
}

void GroupTwo::slotEditReg14()
{
	std::bitset<2> b(reg[11]);
	b[0] = ui.lineEdit_24->text().toInt();
	reg[11] = b.to_ulong();

	updateInfo();
}

void GroupTwo::slotEditReg15()
{
	std::bitset<2> b(reg[11]);
	b[1] = ui.lineEdit_25->text().toInt();
	reg[11] = b.to_ulong();

	updateInfo();
}

//==================================================



void GroupTwo::initReg()
{
//--------------------Абонент 1-----------------------------------------------
	ui.lineEdit->setText(QString::number(reg[0]));
	ui.lineEdit->setInputMask("000");
	ui.lineEdit_2->setText(QString::number(reg[1]));
	ui.lineEdit_2->setInputMask("00");
	QString str = QString::fromStdString(std::bitset<2>(reg[2]).to_string());
	ui.lineEdit_3->setText(str[1]);
	ui.lineEdit_3->setInputMask("B");
	ui.lineEdit_4->setText(str[0]);
	ui.lineEdit_4->setInputMask("B");
//=============================================================================
//---------------------Абонент 2-----------------------------------------------
	ui.lineEdit_5->setText(QString::number(reg[3]));
	ui.lineEdit_5->setInputMask("000");
	ui.lineEdit_6->setText(QString::number(reg[4]));
	ui.lineEdit_6->setInputMask("00");
	str = QString::fromStdString(std::bitset<2>(reg[5]).to_string());
	ui.lineEdit_7->setText(str[1]);
	ui.lineEdit_7->setInputMask("B");
	ui.lineEdit_8->setText(str[0]);
	ui.lineEdit_8->setInputMask("B");

//=============================================================================
//---------------------Абонент 3-----------------------------------------------
	ui.lineEdit_9->setText(QString::number(reg[6]));
	ui.lineEdit_9->setInputMask("000");
	ui.lineEdit_19->setText(QString::number(reg[7]));
	ui.lineEdit_19->setInputMask("00");
	str = QString::fromStdString(std::bitset<2>(reg[8]).to_string());
	ui.lineEdit_20->setText(str[1]);
	ui.lineEdit_20->setInputMask("B");
	ui.lineEdit_21->setText(str[0]);
	ui.lineEdit_21->setInputMask("B");

//=============================================================================
//---------------------Абонент 4-----------------------------------------------
	ui.lineEdit_22->setText(QString::number(reg[9]));
	ui.lineEdit_22->setInputMask("000");
	ui.lineEdit_23->setText(QString::number(reg[10]));
	ui.lineEdit_23->setInputMask("00");
	str = QString::fromStdString(std::bitset<2>(reg[11]).to_string());
	ui.lineEdit_24->setText(str[1]);
	ui.lineEdit_24->setInputMask("B");
	ui.lineEdit_25->setText(str[0]);
	ui.lineEdit_25->setInputMask("B");

//=============================================================================


	updateInfo();
}

void GroupTwo::updateInfo()
{
//------------------Абонент 1--------------------------------------------------
	if (reg[2] & 1)
		ui.label_7->setText("Автовызов, Да");
	else
		ui.label_7->setText("Автовызов, Нет");

	if (reg[2] & 2)
		ui.label_9->setText("Поддежка связи, Да");
	else
		ui.label_9->setText("Поддежка связи, Нет");
//=============================================================================	
//------------------Абонент 2--------------------------------------------------
	if (reg[5] & 1)
		ui.label_18->setText("Автовызов, Да");
	else
		ui.label_18->setText("Автовызов, Нет");

	if (reg[5] & 2)
		ui.label_19->setText("Поддежка связи, Да");
	else
		ui.label_19->setText("Поддежка связи, Нет");
//=============================================================================

//------------------Абонент 3--------------------------------------------------
	if (reg[8] & 1)
		ui.label_50->setText("Автовызов, Да");
	else
		ui.label_50->setText("Автовызов, Нет");

	if (reg[8] & 2)
		ui.label_51->setText("Поддежка связи, Да");
	else
		ui.label_51->setText("Поддежка связи, Нет");
//=============================================================================

//------------------Абонент 4--------------------------------------------------
	if (reg[11] & 1)
		ui.label_94->setText("Автовызов, Да");
	else
		ui.label_94->setText("Автовызов, Нет");

	if (reg[11] & 2)
		ui.label_95->setText("Поддежка связи, Да");
	else
		ui.label_95->setText("Поддежка связи, Нет");
//=============================================================================


}
