﻿#include "Panel.h"
// APanel
//------------------------------------------------------------------------------------------------------------
APanel::APanel(unsigned short x_pos, unsigned short y_pos, unsigned short width, unsigned short height, CHAR_INFO* screen_buffer, unsigned short screen_width)
:X_Pos(x_pos), Y_Pos(y_pos), Width(width), Height(height), Screen_Buffer(screen_buffer), Screen_Width(screen_width)
{

}
void APanel::Draw()
{
	CHAR_INFO horizontal_symbol{};
	CHAR_INFO vertical_symbol{};
	XYPos horizontal_pos(1, 0, Screen_Width, Width - 2);
	XYPos vertical_pos(1, 0, Screen_Width, Width - 2);

	horizontal_symbol.Char.UnicodeChar = L'═';
	horizontal_symbol.Attributes = 0x1b;

	vertical_symbol.Char.UnicodeChar = L'║';
	vertical_symbol.Attributes = 0x1b;

	// 1. Horizontal linesa
	// 1.1 Upper line
	Draw_Line_Horizontal(Screen_Buffer, horizontal_pos, horizontal_symbol);

	// 1.2 Lower line
	horizontal_pos.Y_Pos = Height - 1;
	Draw_Line_Horizontal(Screen_Buffer, horizontal_pos, horizontal_symbol);

	// 1.3 Middle line
	horizontal_symbol.Char.UnicodeChar = L'─';
	horizontal_pos.Y_Pos = Height - 3;
	Draw_Line_Horizontal(Screen_Buffer, horizontal_pos, horizontal_symbol);

	// 2. Vertical linesa
	// 2.1 Left line
	vertical_pos.Y_Pos = 1;
	Draw_Line_Vertical(Screen_Buffer, vertical_pos, vertical_symbol);




	//Show_Colors(Screen_Buffer, x_y_pos, symbol);
}
//------------------------------------------------------------------------------------------------------------