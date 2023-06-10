#pragma once

#include <windows.h>
#include "Asm_Tools_Interface.h"

//------------------------------------------------------------------------------------------------------------
struct XYPos
{
	XYPos(unsigned short x_pos, unsigned short y_pos, unsigned short screen_width, unsigned short length);

	unsigned short X_Pos;
	unsigned short Y_Pos;
	unsigned short Screen_Width;
	unsigned short Length;
};
//------------------------------------------------------------------------------------------------------------
struct SArea_Pos
{
	SArea_Pos(unsigned short x_pos, unsigned short y_pos, unsigned short screen_width, unsigned char width, unsigned char height);

	unsigned short X_Pos;
	unsigned short Y_Pos;
	unsigned short Screen_Width;
	unsigned char Width, Height;
};
//------------------------------------------------------------------------------------------------------------
class ASymbol
{
public:
	ASymbol(wchar_t main_symbol, unsigned short attributes, wchar_t start_symbol, wchar_t end_symbol);

	wchar_t Main_Symbol;
	unsigned short Attributes;
	wchar_t Start_Symbol;
	wchar_t End_Symbol;
};
//------------------------------------------------------------------------------------------------------------
class APanel
{
public:
	APanel(unsigned short x_pos, unsigned short y_pos, unsigned short width, unsigned short height, CHAR_INFO* screen_buffer, unsigned short screen_width);

	void Draw();

	unsigned short X_Pos, Y_Pos;
	unsigned short Width, Height;
	unsigned short Screen_Width;
	CHAR_INFO* Screen_Buffer;
};
//------------------------------------------------------------------------------------------------------------