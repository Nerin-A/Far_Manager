#include "Panel.h"

// ASymbol
//------------------------------------------------------------------------------------------------------------
ASymbol::ASymbol(wchar_t main_symbol, unsigned short attributes, wchar_t first_symbol, wchar_t last_symbol)
: Main_Symbol(main_symbol), Attributes(attributes), First_Symbol(first_symbol), Last_Symbol(last_symbol)
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
	//ASymbol vertical_symbol();
	//XYPos vertical_pos(0, 1, Screen_Width, Height - 2);

	//horizontal_symbol.Char.UnicodeChar = L'═';
	//horizontal_symbol.Attributes = 0x1b;

	//vertical_symbol.Char.UnicodeChar = L'║';
	//vertical_symbol.Attributes = 0x1b;

	// 1. Horizontal lines
	// 1.1 Upper line
	{
		ASymbol horizontal_symbol(L'═', 0x1b, L'╔', L'╗');
		XYPos horizontal_pos(0, 0, Screen_Width, Width - 2);
		Draw_Line_Horizontal(Screen_Buffer, horizontal_pos, horizontal_symbol);
	}

	// 1.2 Lower line
	{
		ASymbol horizontal_symbol(L'═', 0x1b, L'╚', L'╝');
		XYPos horizontal_pos(0, Height - 1, Screen_Width, Width - 2);
		Draw_Line_Horizontal(Screen_Buffer, horizontal_pos, horizontal_symbol);
	}

	// 2. Vertical lines
	// 2.1 Left line
	{
		ASymbol vertical_symbol(L'║', 0x1b, L'║', L'║');
		XYPos vertical_pos(0, 1, Screen_Width, Height - 3);
		Draw_Line_Vertical(Screen_Buffer, vertical_pos, vertical_symbol);
	}

	// 2.2 Right line
	{
		ASymbol vertical_symbol(L'║', 0x1b, L'║', L'║');
		XYPos vertical_pos(Width - 1, 1, Screen_Width, Height - 3);
		Draw_Line_Vertical(Screen_Buffer, vertical_pos, vertical_symbol);
	}

	// 2.3 Middle horizontal line
	{
		ASymbol horizontal_symbol(L'─', 0x1b, L'╟', L'╢');
		XYPos horizontal_pos(0, Height - 3, Screen_Width, Width - 2);
		Draw_Line_Horizontal(Screen_Buffer, horizontal_pos, horizontal_symbol);
	}

	// 2.4 Middle vertical line
	{
		ASymbol vertical_symbol(L'║', 0x1b, L'╦', L'╨');
		XYPos vertical_pos(Width / 2, 0, Screen_Width, Height - 3);
		Draw_Line_Vertical(Screen_Buffer, vertical_pos, vertical_symbol);
	}


	//Show_Colors(Screen_Buffer, x_y_pos, symbol);
}
//------------------------------------------------------------------------------------------------------------