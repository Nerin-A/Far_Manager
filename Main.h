#pragma once

#include <stdio.h>
#include "Panel.h"

//------------------------------------------------------------------------------------------------------------
class AsCommander
{
public:
	~AsCommander();

	bool Init();
	bool Draw();

private:
	HANDLE Std_Handle = 0;
	HANDLE Screen_Buffer_Handle = 0;
	APanel* Left_Panel = 0;
	APanel* Right_Panel = 0;
};
//------------------------------------------------------------------------------------------------------------