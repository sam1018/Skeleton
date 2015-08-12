#pragma once

#include "SkeletonInterface.h"

class SKELETONINTERFACE_DECLSPEC IMainWindow
{
public:
	IMainWindow();
	virtual ~IMainWindow();

	virtual void Show() = 0;
};
