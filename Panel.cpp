#include "Panel.h"

// ASymbol
//------------------------------------------------------------------------------------------------------------
ASymbol::ASymbol(wchar_t main_symbol, unsigned short attributes, wchar_t start_symbol, wchar_t end_symbol)
: Main_Symbol(main_symbol), Attributes(attributes), Start_Symbol(start_symbol), End_Symbol(end_symbol)
{

}
//------------------------------------------------------------------------------------------------------------


// APanel
//------------------------------------------------------------------------------------------------------------
APanel::APanel(unsigned short x_pos, unsigned short y_pos, unsigned short width, unsigned short height, CHAR_INFO* screen_buffer, unsigned short screen_width)
:X_Pos(x_pos), Y_Pos(y_pos), Width(width), Height(height), Screen_Buffer(screen_buffer), Screen_Width(screen_width)
{

}
void APanel::Draw()
{
	Clear_Area(Screen_Buffer, position, symbol);

	// 1. Horizontal lines
	// 1.1 Upper line
	{
		ASymbol symbol(L'═', 0x1b, L'╔', L'╗');
		XYPos position(0, 0, Screen_Width, Width - 2);
		Draw_Line_Horizontal(Screen_Buffer, position, symbol);
	}

	// 1.2 Lower line
	{
		ASymbol symbol(L'═', 0x1b, L'╚', L'╝');
		XYPos position(0, Height - 1, Screen_Width, Width - 2);
		Draw_Line_Horizontal(Screen_Buffer, position, symbol);
	}

	// 2. Vertical lines
	// 2.1 Left line
	{
		ASymbol symbol(L'║', 0x1b, L'║', L'║');
		XYPos position(0, 1, Screen_Width, Height - 4);
		Draw_Line_Vertical(Screen_Buffer, position, symbol);
	}

	// 2.2 Right line
	{
		ASymbol symbol(L'║', 0x1b, L'║', L'║');
		XYPos position(Width - 1, 1, Screen_Width, Height - 4);
		Draw_Line_Vertical(Screen_Buffer, position, symbol);
	}

	// 3 Middle lines
	// 3.1 Middle horizontal line
	{
		ASymbol symbol(L'─', 0x1b, L'╟', L'╢');
		XYPos position(0, Height - 3, Screen_Width, Width - 2);
		Draw_Line_Horizontal(Screen_Buffer, position, symbol);
	}

	// 3.2 Middle vertical line
	{
		ASymbol symbol(L'║', 0x1b, L'╦', L'╨');
		XYPos position(Width / 2, 0, Screen_Width, Height - 4);
		Draw_Line_Vertical(Screen_Buffer, position, symbol);
	}


	//Show_Colors(Screen_Buffer, x_y_pos, symbol);
}
//------------------------------------------------------------------------------------------------------------