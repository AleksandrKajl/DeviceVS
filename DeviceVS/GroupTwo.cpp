#include"GroupTwo.h"
#include<bitset>

GroupTwo::GroupTwo(QWidget* parent) 
	: QMainWindow(parent)
{
	ui.setupUi(this);

	reg[0] = 77;
	reg[1] = 3;
	reg[2] = 2;	//reg3[D:0] è reg4[D1]
	connect(ui.lineEdit, SIGNAL(editingFinished()), SLOT(slotEditReg0()));
	connect(ui.lineEdit_2, SIGNAL(editingFinished()), SLOT(slotEditReg1()));
	connect(ui.lineEdit_3, SIGNAL(editingFinished()), SLOT(slotEditReg2()));
	connect(ui.lineEdit_4, SIGNAL(editingFinished()), SLOT(slotEditReg3()));

	initReg();

}

void GroupTwo::slotEditReg0()
{
	reg[0] = ui.lineEdit->text().toInt();
}

void GroupTwo::slotEditReg1()
{
	reg[1] = ui.lineEdit->text().toInt();
}

void GroupTwo::slotEditReg2()
{
	reg[2] &= (0xFF & ui.lineEdit->text().toInt());
}

void GroupTwo::slotEditReg3()
{
}

void GroupTwo::initReg()
{
	ui.lineEdit->setText(QString::number(reg[0]));
	ui.lineEdit->setInputMask("000");
	ui.lineEdit_2->setText(QString::number(reg[1]));
	ui.lineEdit_2->setInputMask("00");
	QString str = QString::fromStdString(std::bitset<2>(reg[2]).to_string());
	ui.lineEdit_3->setText(str[1]);
	ui.lineEdit_3->setInputMask("B");
	ui.lineEdit_4->setText(str[0]);
	ui.lineEdit_4->setInputMask("B");

}

void GroupTwo::updateInfo()
{

}
