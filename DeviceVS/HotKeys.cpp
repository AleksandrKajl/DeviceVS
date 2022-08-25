#include"HotKeys.h"
#include<QKeyEvent>


HotKeys::HotKeys()
{
}

HotKeys::~HotKeys()
{
}

std::optional<QKeyEvent*> HotKeys::keysProcessing(DeviceVS* pDev, QKeyEvent* pe)
{
    switch (pe->key())
    {
    case Qt::Key_O:
        if (pe->modifiers() & Qt::ControlModifier)
            pDev->slotLoadSettings();
        break;
    case Qt::Key_S:
        if (pe->modifiers() & Qt::ControlModifier)
            pDev->slotSaveSettings();
        break;
    case Qt::Key_J:
        if (pe->modifiers() & Qt::ControlModifier)
            pDev->slotOpenLog();
        break;
    case Qt::Key_I:
        if (pe->modifiers() & Qt::ControlModifier)
            pDev->slotInfo();
        break;
    case Qt::Key_Q:
        if (pe->modifiers() & Qt::ControlModifier)
            pDev->close();
        break;
    default:
        return pe;
    }
    return std::nullopt;
}
