#pragma once

#include <stdio.h>
#include "Panel.h"

//------------------------------------------------------------------------------------------------------------
class AMenu_Item
{
public:
	AMenu_Item(unsigned short x_pos, unsigned short y_pos, const wchar_t* key, const wchar_t* name, unsigned short length);

	void Draw(CHAR_INFO* screen_buffer, unsigned short screen_width);

	unsigned short X_Pos;
	unsigned short Y_Pos;
	const wchar_t* Key, *Name;
	unsigned short Length;
};
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
	CHAR_INFO* Screen_Buffer = 0;
	CONSOLE_SCREEN_BUFFER_INFO Screen_Buffer_Info{};
	APanel* Left_Panel = 0;
	APanel* Right_Panel = 0;
};
//------------------------------------------------------------------------------------------------------------