#include"GroupTwo.h"


GroupTwo::GroupTwo(DeviceVS* pDevice)
    : QObject(pDevice)
    , m_pDev(pDevice)
    , m_pValidReg8(new QIntValidator(0, 999, this))
    , m_pValidReg9(new QIntValidator(0, 99, this))
{
    //----------------Абонент 1-------------------------------------------------------------
    connect(m_pDev->ui.lineEdit_7, SIGNAL(editingFinished()), SLOT(slotEditReg8()));
    connect(m_pDev->ui.lineEdit_8, SIGNAL(editingFinished()), SLOT(slotEditReg9()));
    connect(m_pDev->ui.lineEdit_9, SIGNAL(editingFinished()), SLOT(slotEditReg10_0()));
    connect(m_pDev->ui.lineEdit_10, SIGNAL(editingFinished()), SLOT(slotEditReg10_1()));
    //======================================================================================
    //----------------Абонент 2-------------------------------------------------------------
    connect(m_pDev->ui.lineEdit_11, SIGNAL(editingFinished()), SLOT(slotEditReg11()));
    connect(m_pDev->ui.lineEdit_12, SIGNAL(editingFinished()), SLOT(slotEditReg12()));
    connect(m_pDev->ui.lineEdit_13, SIGNAL(editingFinished()), SLOT(slotEditReg13_0()));
    connect(m_pDev->ui.lineEdit_14, SIGNAL(editingFinished()), SLOT(slotEditReg13_1()));
    //======================================================================================
    // 
    //----------------Абонент 3-------------------------------------------------------------
    connect(m_pDev->ui.lineEdit_15, SIGNAL(editingFinished()), SLOT(slotEditReg14()));
    connect(m_pDev->ui.lineEdit_16, SIGNAL(editingFinished()), SLOT(slotEditReg15()));
    connect(m_pDev->ui.lineEdit_17, SIGNAL(editingFinished()), SLOT(slotEditReg16_0()));
    connect(m_pDev->ui.lineEdit_18, SIGNAL(editingFinished()), SLOT(slotEditReg16_1()));
    //======================================================================================
    //----------------Абонент 4-------------------------------------------------------------
    connect(m_pDev->ui.lineEdit_19, SIGNAL(editingFinished()), SLOT(slotEditReg17()));
    connect(m_pDev->ui.lineEdit_20, SIGNAL(editingFinished()), SLOT(slotEditReg18()));
    connect(m_pDev->ui.lineEdit_21, SIGNAL(editingFinished()), SLOT(slotEditReg19_0()));
    connect(m_pDev->ui.lineEdit_22, SIGNAL(editingFinished()), SLOT(slotEditReg19_1()));
    //======================================================================================

    //Устанавливаем валидаторы 
    m_pDev->ui.lineEdit_7->setValidator(m_pValidReg8);
    m_pDev->ui.lineEdit_8->setValidator(m_pValidReg9);

    m_pDev->ui.lineEdit_11->setValidator(m_pValidReg8);
    m_pDev->ui.lineEdit_12->setValidator(m_pValidReg9);

    m_pDev->ui.lineEdit_15->setValidator(m_pValidReg8);
    m_pDev->ui.lineEdit_16->setValidator(m_pValidReg9);

    m_pDev->ui.lineEdit_19->setValidator(m_pValidReg8);
    m_pDev->ui.lineEdit_20->setValidator(m_pValidReg9);

    initReg();
}

void GroupTwo::slotEditReg8()
{
    uint16_t reg = m_pDev->ui.lineEdit_7->text().toInt();
    //Если привышает один байт записываем 0xFF
    if (reg > 255)
        m_pDev->m_reg[8] = 255;
    else
        m_pDev->m_reg[8] = reg;

    updateInfo();
}

void GroupTwo::slotEditReg9()
{
    m_pDev->m_reg[9] = m_pDev->ui.lineEdit_8->text().toInt();
    updateInfo();
}

void GroupTwo::slotEditReg10_0()
{
    std::bitset<2> rg10(m_pDev->m_reg[10]);
    rg10[0] = m_pDev->ui.lineEdit_9->text().toInt();
    m_pDev->m_reg[10] = rg10.to_ulong();

    updateInfo();
}

void GroupTwo::slotEditReg10_1()
{
    std::bitset<2> rg10(m_pDev->m_reg[10]);
    rg10[1] = m_pDev->ui.lineEdit_10->text().toInt();
    m_pDev->m_reg[10] = rg10.to_ulong();

    updateInfo();
}

void GroupTwo::slotEditReg11()
{
    uint16_t reg = m_pDev->ui.lineEdit_11->text().toInt();
    //Если привышает один байт записываем 0xFF
    if (reg > 255)
        m_pDev->m_reg[11] = 255;
    else
        m_pDev->m_reg[11] = reg;
    updateInfo();
}

void GroupTwo::slotEditReg12()
{
    m_pDev->m_reg[12] = m_pDev->ui.lineEdit_12->text().toInt();
    updateInfo();
}

void GroupTwo::slotEditReg13_0()
{
    std::bitset<2> rg13(m_pDev->m_reg[13]);
    rg13[0] = m_pDev->ui.lineEdit_13->text().toInt();
    m_pDev->m_reg[13] = rg13.to_ulong();

    updateInfo();
}

void GroupTwo::slotEditReg13_1()
{
    std::bitset<2> rg13(m_pDev->m_reg[13]);
    rg13[1] = m_pDev->ui.lineEdit_14->text().toInt();
    m_pDev->m_reg[13] = rg13.to_ulong();

    updateInfo();
}

void GroupTwo::slotEditReg14()
{
    uint16_t reg = m_pDev->ui.lineEdit_15->text().toInt();
    //Если привышает один байт записываем 0xFF
    if (reg > 255)
        m_pDev->m_reg[14] = 255;
    else
        m_pDev->m_reg[14] = reg;
    updateInfo();
}

void GroupTwo::slotEditReg15()
{
    m_pDev->m_reg[15] = m_pDev->ui.lineEdit_16->text().toInt();
    updateInfo();
}

void GroupTwo::slotEditReg16_0()
{
    std::bitset<2> rg16(m_pDev->m_reg[16]);
    rg16[0] = m_pDev->ui.lineEdit_17->text().toInt();
    m_pDev->m_reg[16] = rg16.to_ulong();

    updateInfo();
}

void GroupTwo::slotEditReg16_1()
{
    std::bitset<2> rg16(m_pDev->m_reg[16]);
    rg16[1] = m_pDev->ui.lineEdit_18->text().toInt();
    m_pDev->m_reg[16] = rg16.to_ulong();

    updateInfo();
}

void GroupTwo::slotEditReg17()
{
    uint16_t reg = m_pDev->ui.lineEdit_19->text().toInt();
    //Если привышает один байт записываем 0xFF
    if (reg > 255)
        m_pDev->m_reg[17] = 255;
    else
        m_pDev->m_reg[17] = reg;

    updateInfo();
}

void GroupTwo::slotEditReg18()
{
    
    m_pDev->m_reg[18] = m_pDev->ui.lineEdit_20->text().toInt();
    updateInfo();
}

void GroupTwo::slotEditReg19_0()
{
    std::bitset<2> rg19(m_pDev->m_reg[19]);
    rg19[0] = m_pDev->ui.lineEdit_21->text().toInt();
    m_pDev->m_reg[19] = rg19.to_ulong();

    updateInfo();
}

void GroupTwo::slotEditReg19_1()
{
    std::bitset<2> rg19(m_pDev->m_reg[19]);
    rg19[1] = m_pDev->ui.lineEdit_22->text().toInt();
    m_pDev->m_reg[19] = rg19.to_ulong();

    updateInfo();
}

void GroupTwo::initReg()
{
    //ИНИЦИАЛИЗАЦИЯ ГРУППЫ РЕГИСТРОВ ДВА
//--------------------Абонент 1-----------------------------------------------
    m_pDev->ui.lineEdit_7->setText(QString::number((uint8_t)m_pDev->m_reg[8]));
    m_pDev->ui.lineEdit_8->setText(QString::number((uint8_t)m_pDev->m_reg[9]));
    QString str = QString::fromStdString(std::bitset<2>(m_pDev->m_reg[10]).to_string());
    m_pDev->ui.lineEdit_9->setText(str[1]);
    m_pDev->ui.lineEdit_9->setInputMask("B");
    m_pDev->ui.lineEdit_10->setText(str[0]);
    m_pDev->ui.lineEdit_10->setInputMask("B");
    //=============================================================================
    //---------------------Абонент 2-----------------------------------------------
    m_pDev->ui.lineEdit_11->setText(QString::number((uint8_t)m_pDev->m_reg[11]));
    m_pDev->ui.lineEdit_12->setText(QString::number((uint8_t)m_pDev->m_reg[12]));
    str = QString::fromStdString(std::bitset<2>(m_pDev->m_reg[13]).to_string());
    m_pDev->ui.lineEdit_13->setText(str[1]);
    m_pDev->ui.lineEdit_13->setInputMask("B");
    m_pDev->ui.lineEdit_14->setText(str[0]);
    m_pDev->ui.lineEdit_14->setInputMask("B");

    //=============================================================================
    //---------------------Абонент 3-----------------------------------------------
    m_pDev->ui.lineEdit_15->setText(QString::number((uint8_t)m_pDev->m_reg[14]));
    m_pDev->ui.lineEdit_16->setText(QString::number((uint8_t)m_pDev->m_reg[15]));
    str = QString::fromStdString(std::bitset<2>(m_pDev->m_reg[16]).to_string());
    m_pDev->ui.lineEdit_17->setText(str[1]);
    m_pDev->ui.lineEdit_17->setInputMask("B");
    m_pDev->ui.lineEdit_18->setText(str[0]);
    m_pDev->ui.lineEdit_18->setInputMask("B");

    //=============================================================================
    //---------------------Абонент 4-----------------------------------------------
    m_pDev->ui.lineEdit_19->setText(QString::number((uint8_t)m_pDev->m_reg[17]));
    m_pDev->ui.lineEdit_20->setText(QString::number((uint8_t)m_pDev->m_reg[18]));
    str = QString::fromStdString(std::bitset<2>(m_pDev->m_reg[19]).to_string());
    m_pDev->ui.lineEdit_21->setText(str[1]);
    m_pDev->ui.lineEdit_21->setInputMask("B");
    m_pDev->ui.lineEdit_22->setText(str[0]);
    m_pDev->ui.lineEdit_22->setInputMask("B");
    //=============================================================================

    updateInfo();
}

void GroupTwo::updateInfo()
{
    QString err("Не верное значение");
   //ОБНОВЛЕНИЕ ИНФОРМАЦИИ О ГРУППЕ РЕГИСТРОВ ДВА
  //------------------Абонент 1--------------------------------------------------
    //РГ8
    if((uint8_t)m_pDev->m_reg[8] > 100)
        m_pDev->ui.label_11->setText(err);
    else
        m_pDev->ui.label_11->setText("Идинтификатор абонента");

    //РГ9
    if (m_pDev->m_reg[9] > 10)
        m_pDev->ui.label_21->setText(err);
    else
        m_pDev->ui.label_21->setText("Номер канала");
    
    //РГ10_0
    if (m_pDev->m_reg[10] & 1)
        m_pDev->ui.label_22->setText("Автовызов: Да");
    else
        m_pDev->ui.label_22->setText("Автовызов: Нет");

    //РГ10_1
    if (m_pDev->m_reg[10] & 2)
        m_pDev->ui.label_24->setText("Поддержание связи: Да");
    else
        m_pDev->ui.label_24->setText("Поддержание связи: Нет");
    //=============================================================================	
    //------------------Абонент 2--------------------------------------------------
    //РГ11
    if ((uint8_t)m_pDev->m_reg[11] > 100)
        m_pDev->ui.label_27->setText(err);
    else
        m_pDev->ui.label_27->setText("Идинтификатор абонента");

    //РГ12
    if (m_pDev->m_reg[12] > 10)
        m_pDev->ui.label_29->setText(err);
    else
        m_pDev->ui.label_29->setText("Номер канала");
    
    //РГ13_0
    if (m_pDev->m_reg[13] & 1)
        m_pDev->ui.label_31->setText("Автовызов: Да");
    else
        m_pDev->ui.label_31->setText("Автовызов: Нет");

    //РГ13_1
    if (m_pDev->m_reg[13] & 2)
        m_pDev->ui.label_33->setText("Поддержание связи: Да");
    else
        m_pDev->ui.label_33->setText("Поддержание связи: Нет");
    //=============================================================================

    //------------------Абонент 3--------------------------------------------------
    //РГ14
    if ((uint8_t)m_pDev->m_reg[14] > 100)
        m_pDev->ui.label_36->setText(err);
    else
        m_pDev->ui.label_36->setText("Идинтификатор абонента");

    //РГ15
    if (m_pDev->m_reg[15] > 10)
        m_pDev->ui.label_38->setText(err);
    else
        m_pDev->ui.label_38->setText("Номер канала");

    //РГ16_0
    if (m_pDev->m_reg[16] & 1)
        m_pDev->ui.label_40->setText("Автовызов: Да");
    else
        m_pDev->ui.label_40->setText("Автовызов: Нет");

    //РГ16_1
    if (m_pDev->m_reg[16] & 2)
        m_pDev->ui.label_42->setText("Поддержание связи: Да");
    else
        m_pDev->ui.label_42->setText("Поддержание связи: Нет");
    //=============================================================================

    //------------------Абонент 4--------------------------------------------------
    //РГ17
    if ((uint8_t)m_pDev->m_reg[17] > 100)
        m_pDev->ui.label_45->setText(err);
    else
        m_pDev->ui.label_45->setText("Идинтификатор абонента");

    //РГ18
    if (m_pDev->m_reg[18] > 10)
        m_pDev->ui.label_47->setText(err);
    else
        m_pDev->ui.label_47->setText("Номер канала");

    //РГ19_0
    if (m_pDev->m_reg[19] & 1)
        m_pDev->ui.label_49->setText("Автовызов: Да");
    else
        m_pDev->ui.label_49->setText("Автовызов: Нет");

    //РГ19_1
    if (m_pDev->m_reg[19] & 2)
        m_pDev->ui.label_51->setText("Поддержание связи: Да");
    else
        m_pDev->ui.label_51->setText("Поддержание связи: Нет");
    //=============================================================================
}