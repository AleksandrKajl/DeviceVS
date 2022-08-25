#pragma once
#include"DeviceVS.h"
#include<optional>

class HotKeys
{
public:
	HotKeys();
	~HotKeys();

	std::optional<QKeyEvent*> keysProcessing(DeviceVS* pDev, QKeyEvent* pe);
};