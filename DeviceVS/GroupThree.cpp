#include"GroupThree.h"

GroupThree::GroupThree(DeviceVS* pDevice)
    : QObject(pDevice)
    , m_pDev(pDevice)
    , m_pValid(new QIntValidator(0, 999, this))
    , rg32(0)
    , rg34(0)
{
    //ГРУППА РЕГИСТРОВ ТРИ
    connect(m_pDev->ui.lineEdit_23, SIGNAL(editingFinished()), SLOT(slotEditReg32_0()));
    connect(m_pDev->ui.lineEdit_24, SIGNAL(editingFinished()), SLOT(slotEditReg32_2_1()));
    connect(m_pDev->ui.lineEdit_25, SIGNAL(editingFinished()), SLOT(slotEditReg32_4_3()));
    connect(m_pDev->ui.lineEdit_26, SIGNAL(editingFinished()), SLOT(slotEditReg32_5()));
    connect(m_pDev->ui.lineEdit_27, SIGNAL(editingFinished()), SLOT(slotEditReg33()));
    connect(m_pDev->ui.lineEdit_28, SIGNAL(editingFinished()), SLOT(slotEditReg34_0()));
    connect(m_pDev->ui.lineEdit_29, SIGNAL(editingFinished()), SLOT(slotEditReg34_1()));
    connect(m_pDev->ui.lineEdit_30, SIGNAL(editingFinished()), SLOT(slotEditReg34_2()));
    connect(m_pDev->ui.lineEdit_31, SIGNAL(editingFinished()), SLOT(slotEditReg34_3()));

    m_pDev->ui.lineEdit_27->setValidator(m_pValid);

    initReg();
}

void GroupThree::slotEditReg32_0()
{
    rg32 = m_pDev->m_reg[32];
    rg32[0] = m_pDev->ui.lineEdit_23->text().toInt();
    m_pDev->m_reg[32] = rg32.to_ulong();

    updateInfo();
}

void GroupThree::slotEditReg32_2_1()
{
    rg32 = m_pDev->m_reg[32];
    bool res;
    uint8_t bits = m_pDev->ui.lineEdit_24->text().toInt(&res, 2);
    if (res)
    {
        switch (bits)
        {
        case 0:
            rg32[1] = 0;
            rg32[2] = 0;
            break;
        case 1:
            rg32[1] = 1;
            rg32[2] = 0;
            break;
        case 2:
            rg32[1] = 0;
            rg32[2] = 1;
            break;
        case 3:
            rg32[1] = 1;
            rg32[2] = 1;
        }

        m_pDev->m_reg[32] = rg32.to_ulong();
    }
    else
        QMessageBox::warning(nullptr, "Warning lineEdit_24", "Вы ввели пустое значение");

    updateInfo();
}

void GroupThree::slotEditReg32_4_3()
{
    rg32 = m_pDev->m_reg[32];
    bool res;
    char twoBit = m_pDev->ui.lineEdit_25->text().toInt(&res, 2);
    if (res)
    {
        switch (twoBit)
        {
        case 0:
            rg32[3] = 0;
            rg32[4] = 0;
            break;
        case 1:
            rg32[3] = 1;
            rg32[4] = 0;
            break;
        case 2:
            rg32[3] = 0;
            rg32[4] = 1;
            break;
        case 3:
            rg32[3] = 1;
            rg32[4] = 1;
        }
    }
    else
        QMessageBox::warning(nullptr, "Warning lineEdit_25", "Вы ввели пустое значение");

    m_pDev->m_reg[32] = rg32.to_ulong();

    updateInfo();
}

void GroupThree::slotEditReg32_5()
{
    rg32 = m_pDev->m_reg[32];
    rg32[5] = m_pDev->ui.lineEdit_26->text().toInt();
    m_pDev->m_reg[32] = rg32.to_ulong();

    updateInfo();
}

void GroupThree::slotEditReg33()
{
    int rg33 = m_pDev->ui.lineEdit_27->text().toUInt();
    if (rg33 > 255)
        m_pDev->m_reg[33] = 255;
    else
        m_pDev->m_reg[33] = rg33;

    initReg();
}

void GroupThree::slotEditReg34_0()
{
    rg34 = m_pDev->m_reg[34];
    rg34[0] = m_pDev->ui.lineEdit_28->text().toInt();
    m_pDev->m_reg[34] = rg34.to_ulong();

    updateInfo();
}

void GroupThree::slotEditReg34_1()
{
    rg34 = m_pDev->m_reg[34];
    rg34[1] = m_pDev->ui.lineEdit_29->text().toInt();
    m_pDev->m_reg[34] = rg34.to_ulong();

    updateInfo();
}

void GroupThree::slotEditReg34_2()
{
    rg34 = m_pDev->m_reg[34];
    rg34[2] = m_pDev->ui.lineEdit_30->text().toInt();
    m_pDev->m_reg[34] = rg34.to_ulong();

    updateInfo();
}

void GroupThree::slotEditReg34_3()
{
    rg34 = m_pDev->m_reg[34];
    rg34[3] = m_pDev->ui.lineEdit_31->text().toInt();
    m_pDev->m_reg[34] = rg34.to_ulong();

    updateInfo();
}

void GroupThree::initReg()
{
    //ИНИЦИАЛИЗАЦИЯ ГРУППЫ РЕГИСТРОВ ТРИ
    rg32 = m_pDev->m_reg[32];
    QString str = QString::fromStdString(rg32.to_string());
    m_pDev->ui.lineEdit_23->setText(str[5]);
    m_pDev->ui.lineEdit_23->setInputMask("B");
  
    m_pDev->ui.lineEdit_24->setText(str.sliced(3, 2));
    m_pDev->ui.lineEdit_24->setInputMask("bb");

    m_pDev->ui.lineEdit_25->setText(str.sliced(1, 2));
    m_pDev->ui.lineEdit_25->setInputMask("bb");

    m_pDev->ui.lineEdit_26->setText(str[0]);
    m_pDev->ui.lineEdit_26->setInputMask("B");

    m_pDev->ui.lineEdit_27->setText(QString::number((uint8_t)m_pDev->m_reg[33]));
    
    rg34 = m_pDev->m_reg[34];
    str = QString::fromStdString(rg34.to_string());
    m_pDev->ui.lineEdit_28->setText(str[3]);
    m_pDev->ui.lineEdit_28->setInputMask("B");

    m_pDev->ui.lineEdit_29->setText(str[2]);
    m_pDev->ui.lineEdit_29->setInputMask("B");

    m_pDev->ui.lineEdit_30->setText(str[1]);
    m_pDev->ui.lineEdit_30->setInputMask("B");

    m_pDev->ui.lineEdit_31->setText(str[0]);
    m_pDev->ui.lineEdit_31->setInputMask("B");
    
    updateInfo();
}

void GroupThree::updateInfo()
{
    QString err("Не верное значение");
    //РГ32[D0]
    if (m_pDev->m_reg[32] & 1)
    {
        m_pDev->ui.label_55->setText("Модем исправен");
        m_pDev->ui.label_55->setStyleSheet(GREEN_FIELD);
    }
    else
    {
        m_pDev->ui.label_55->setText("Модем не исправен");
        m_pDev->ui.label_55->setStyleSheet(RED_FIELD);
    }

    //РГ32[D2:D1]
    char twoBit = (m_pDev->m_reg[32] >> 1) & 3;

    switch (twoBit)
    {
    case 0:
        m_pDev->ui.label_57->setText("Сигнал: Норма");
        m_pDev->ui.label_57->setStyleSheet(GREEN_FIELD);
        break;
    case 1:
        m_pDev->ui.label_57->setText("Сигнал: Предупреждение");
        m_pDev->ui.label_57->setStyleSheet(YELLOW_FIELD);
        break;
    case 2:
        m_pDev->ui.label_57->setText("Сигнал: Ошибка");
        m_pDev->ui.label_57->setStyleSheet(RED_FIELD);
        break;
    default:
        m_pDev->ui.label_57->setText(err);
        m_pDev->ui.label_57->setStyleSheet(nullptr);
    }

    //РГ32[D4:D3]
    twoBit = (m_pDev->m_reg[32] >> 3) & 3;

    switch (twoBit)
    {
    case(0):
        m_pDev->ui.label_59->setText("Связь: Норма");
        m_pDev->ui.label_59->setStyleSheet(GREEN_FIELD);
        break;
    case(1):
        m_pDev->ui.label_59->setText("Связь: Предупреждение");
        m_pDev->ui.label_59->setStyleSheet(YELLOW_FIELD);
        break;
    case(2):
        m_pDev->ui.label_59->setText("Связь: Ошибка");
        m_pDev->ui.label_59->setStyleSheet(RED_FIELD);
        break;
    default:
        m_pDev->ui.label_59->setText(err);
        m_pDev->ui.label_59->setStyleSheet(nullptr);
    }

    //РГ32[D5]
    if (m_pDev->m_reg[32] >> 5)
    {
        m_pDev->ui.label_61->setText("Наличие информации: Есть");
        m_pDev->ui.label_61->setStyleSheet(GREEN_FIELD);
    }
    else
    {
        m_pDev->ui.label_61->setText("Наличие информации: Нет");
        m_pDev->ui.label_61->setStyleSheet(YELLOW_FIELD);
    }

    //РГ33
    if ((uint8_t)m_pDev->m_reg[33] >= 170)
        m_pDev->ui.label_62->setStyleSheet(GREEN_FIELD);
    else if ((uint8_t)m_pDev->m_reg[33] >= 85)
        m_pDev->ui.label_62->setStyleSheet(YELLOW_FIELD);
    else
        m_pDev->ui.label_62->setStyleSheet(RED_FIELD);

    //РГ34[D0]
    //Обновляем информацию о битах РГ34
    rg34 = m_pDev->m_reg[34];
    if (rg34[0])
    {
        m_pDev->ui.label_65->setText("Связь с абонентом №1: Есть");
        m_pDev->ui.label_65->setStyleSheet(GREEN_FIELD);
    }
    else
    {
        m_pDev->ui.label_65->setText("Связь с абонентом №1: Нет");
        m_pDev->ui.label_65->setStyleSheet(YELLOW_FIELD);
    }


    //РГ34[D1]
    if (rg34[1])
    {
        m_pDev->ui.label_67->setText("Связь с абонентом №2: Есть");
        m_pDev->ui.label_67->setStyleSheet(GREEN_FIELD);
    }
    else
    {
        m_pDev->ui.label_67->setText("Связь с абонентом №2: Нет");
        m_pDev->ui.label_67->setStyleSheet(YELLOW_FIELD);
    }


    //РГ34[D2]
    if (rg34[2])
    {
        m_pDev->ui.label_71->setText("Связь с абонентом №3: Есть");
        m_pDev->ui.label_71->setStyleSheet(GREEN_FIELD);
    }
    else
    {
        m_pDev->ui.label_71->setText("Связь с абонентом №3: Нет");
        m_pDev->ui.label_71->setStyleSheet(YELLOW_FIELD);
    }


    //РГ34[D3]
    if (rg34[3])
    {
        m_pDev->ui.label_72->setText("Связь с абонентом №4: Есть");
        m_pDev->ui.label_72->setStyleSheet(GREEN_FIELD);
    }
    else
    {
        m_pDev->ui.label_72->setText("Связь с абонентом №4: Нет");
        m_pDev->ui.label_72->setStyleSheet(YELLOW_FIELD);
    }
}
