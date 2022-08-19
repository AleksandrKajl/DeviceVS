#include"GroupThree.h"
#include<bitset>
#include<QMessageBox>

GroupThree::GroupThree(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.lineEdit, SIGNAL(editingFinished()), SLOT(slotEditLine()));
	connect(ui.lineEdit_2, SIGNAL(editingFinished()), SLOT(slotEditLine_2()));
	connect(ui.lineEdit_3, SIGNAL(editingFinished()), SLOT(slotEditLine_3()));
	connect(ui.lineEdit_4, SIGNAL(editingFinished()), SLOT(slotEditLine_4()));
	connect(ui.lineEdit_5, SIGNAL(editingFinished()), SLOT(slotEditLine_5()));
	connect(ui.lineEdit_6, SIGNAL(editingFinished()), SLOT(slotEditLine_6()));
	connect(ui.lineEdit_7, SIGNAL(editingFinished()), SLOT(slotEditLine_7()));
	connect(ui.lineEdit_8, SIGNAL(editingFinished()), SLOT(slotEditLine_8()));
	connect(ui.lineEdit_9, SIGNAL(editingFinished()), SLOT(slotEditLine_9()));

	reg[0] = 0b001001;
	reg[1] = 144;
	reg[2] = 0b0011;
	initReg();
}

void GroupThree::slotEditLine()
{
	std::bitset<6> rg32(reg[0]);
	rg32[0] = ui.lineEdit->text().toInt();
	reg[0] = rg32.to_ulong();

	updateInfo();
}

void GroupThree::slotEditLine_2()
{
	std::bitset<6> rg32(reg[0]);
	bool res;
	char twoBit = ui.lineEdit_2->text().toInt(&res,2);
	if (!res)
		QMessageBox::warning(this, "Warning lineEdit_2", "Не возможно перевести строку в число");

	switch (twoBit)
	{
	case(0):
		rg32[1] = 0;
		rg32[2] = 0;
		break;
	case(1):
		rg32[1] = 1;
		rg32[2] = 0;
		break;
	case(2):
		rg32[1] = 0;
		rg32[2] = 1;
		break;
	case(3):
		rg32[1] = 1;
		rg32[2] = 1;
	}
	
	reg[0] = rg32.to_ulong();
	updateInfo();
}

void GroupThree::slotEditLine_3()
{
	std::bitset<6> rg32(reg[0]);
	bool res;
	char twoBit = ui.lineEdit_3->text().toInt(&res, 2);
	if (!res)
		QMessageBox::warning(this, "Warning lineEdit_2", "Не возможно перевести строку в число");

	switch (twoBit)
	{
	case(0):
		rg32[3] = 0;
		rg32[4] = 0;
		break;
	case(1):
		rg32[3] = 1;
		rg32[4] = 0;
		break;
	case(2):
		rg32[3] = 0;
		rg32[4] = 1;
		break;
	case(3):
		rg32[3] = 1;
		rg32[4] = 1;
	}

	reg[0] = rg32.to_ulong();

	updateInfo();
}
void GroupThree::slotEditLine_4()
{
	std::bitset<6> rg32(reg[0]);
	rg32[5] = ui.lineEdit_4->text().toInt();
	reg[0] = rg32.to_ulong();

	updateInfo();
}
void GroupThree::slotEditLine_5()
{
	char rg33 = ui.lineEdit_5->text().toInt();
	if (rg33 > 255)
		reg[1] = 255;
	else
		reg[1] = rg33;

	updateInfo();
}
void GroupThree::slotEditLine_6()
{
	std::bitset<4> rg34(reg[2]);
	rg34[0] = ui.lineEdit_6->text().toInt();
	reg[2] = rg34.to_ulong();

	updateInfo();
}
void GroupThree::slotEditLine_7()
{
	std::bitset<4> rg34(reg[2]);
	rg34[1] = ui.lineEdit_7->text().toInt();
	reg[2] = rg34.to_ulong();

	updateInfo();
}
void GroupThree::slotEditLine_8()
{
	std::bitset<4> rg34(reg[2]);
	rg34[2] = ui.lineEdit_8->text().toInt();
	reg[2] = rg34.to_ulong();

	updateInfo();
}
void GroupThree::slotEditLine_9()
{
	std::bitset<4> rg34(reg[2]);
	rg34[3] = ui.lineEdit_9->text().toInt();
	reg[2] = rg34.to_ulong();

	updateInfo();
}

void GroupThree::initReg()
{
	std::bitset<6> rg32(reg[0]);
	QString str = QString::fromStdString(rg32.to_string());
	ui.lineEdit->setText(str[5]);
	ui.lineEdit->setInputMask("B");
	ui.lineEdit_2->setText("11");
	ui.lineEdit_2->setText(str.sliced(3,2));
	ui.lineEdit_2->setInputMask("BB");
	ui.lineEdit_3->setText(str.sliced(1, 2));
	ui.lineEdit_3->setInputMask("BB");
	ui.lineEdit_4->setText(str[0]);
	ui.lineEdit_4->setInputMask("B");
	ui.lineEdit_5->setText(QString::number(reg[1]));
	ui.lineEdit_5->setInputMask("009");
	std::bitset<4> rg34(reg[2]);
	str = QString::fromStdString(rg34.to_string());
	ui.lineEdit_6->setText(str[3]);
	ui.lineEdit_6->setInputMask("B");
	ui.lineEdit_7->setText(str[2]);
	ui.lineEdit_7->setInputMask("B");
	ui.lineEdit_8->setText(str[1]);
	ui.lineEdit_8->setInputMask("B");
	ui.lineEdit_9->setText(str[0]);
	ui.lineEdit_9->setInputMask("B");

	updateInfo();
}

void GroupThree::updateInfo()
{
	//РГ32[D0]
	if (reg[0] & 1)
	{
		ui.label_3->setText("Модем исправен");
		ui.label_3->setStyleSheet("QLabel { background-color : green; color : black; }");
	}
	else
	{
		ui.label_3->setText("Модем не исправен");
		ui.label_3->setStyleSheet("QLabel { background-color : red; color : black; }");
	}
		
	//РГ32[D2:D1]
	char twoBit = (reg[0] >> 1) & 3;

	switch (twoBit)
	{
	case(0):
		ui.label_5->setText("Сигнал: Норма");
		ui.label_5->setStyleSheet("QLabel { background-color : green; color : black; }");
		break;
	case(1):
		ui.label_5->setText("Сигнал: Предупреждение");
		ui.label_5->setStyleSheet("QLabel { background-color : yellow; color : black; }");
		break;
	case(2):
		ui.label_5->setText("Сигнал: Ошибка");
		ui.label_5->setStyleSheet("QLabel { background-color : red; color : black; }");
	}

	//РГ32[D4:D3]
	twoBit = (reg[0] >> 3) & 3;

	switch (twoBit)
	{
	case(0):
		ui.label_8->setText("Связь: Норма");
		ui.label_8->setStyleSheet("QLabel { background-color : green; color : black; }");
		break;
	case(1):
		ui.label_8->setText("Связь: Предупреждение");
		ui.label_8->setStyleSheet("QLabel { background-color : yellow; color : black; }");
		break;
	case(2):
		ui.label_8->setText("Связь: Ошибка");
		ui.label_8->setStyleSheet("QLabel { background-color : red; color : black; }");
	}

	//РГ32[D5]
	if (reg[0] >> 5)
	{
		ui.label_10->setText("Наличие информации: Есть");
		ui.label_10->setStyleSheet("QLabel { background-color : green; color : black; }");
	}
	else
	{
		ui.label_10->setText("Наличие информации: Нет");
		ui.label_10->setStyleSheet("QLabel { background-color : yellow; color : black; }");
	}
		
	//РГ33
	if (reg[1] >= 170)
		ui.label_12->setStyleSheet("QLabel { background-color : green; color : black; }");
	else if(reg[1] >= 85)
		ui.label_12->setStyleSheet("QLabel { background-color : yellow; color : black; }");
	else
		ui.label_12->setStyleSheet("QLabel { background-color : red; color : black; }");

	std::bitset<4> rg34(reg[2]);
	//РГ34[D0]
	if (rg34[0])
	{
		ui.label_14->setText("Связь с абонентом №1: Есть");
		ui.label_14->setStyleSheet("QLabel { background-color : green; color : black; }");
	}
	else
	{
		ui.label_14->setText("Связь с абонентом №1: Нет");
		ui.label_14->setStyleSheet("QLabel { background-color : yellow; color : black; }");
	}
		
	
	//РГ34[D1]
	if (rg34[1])
	{
		ui.label_16->setText("Связь с абонентом №2: Есть");
		ui.label_16->setStyleSheet("QLabel { background-color : green; color : black; }");
	}
	else
	{
		ui.label_16->setText("Связь с абонентом №2: Нет");
		ui.label_16->setStyleSheet("QLabel { background-color : yellow; color : black; }");
	}
		

	//РГ34[D2]
	if (rg34[2])
	{
		ui.label_18->setText("Связь с абонентом №3: Есть");
		ui.label_18->setStyleSheet("QLabel { background-color : green; color : black; }");
	}	
	else
	{
		ui.label_18->setText("Связь с абонентом №3: Нет");
		ui.label_18->setStyleSheet("QLabel { background-color : yellow; color : black; }");
	}
		

	//РГ34[D3]
	if (rg34[3])
	{
		ui.label_20->setText("Связь с абонентом №4: Есть");
		ui.label_20->setStyleSheet("QLabel { background-color : green; color : black; }");
	}
	else
	{
		ui.label_20->setText("Связь с абонентом №4: Нет");
		ui.label_20->setStyleSheet("QLabel { background-color : yellow; color : black; }");
	}
		
}
