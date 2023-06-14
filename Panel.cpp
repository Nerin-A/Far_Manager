#include "Panel.h"

// AFile_Descriptor
//------------------------------------------------------------------------------------------------------------
AFile_Descriptor::AFile_Descriptor(unsigned int attributes, unsigned int size_low, unsigned int size_high, wchar_t* file_name)
	:Attributes(attributes), Filename(file_name)
{
	File_Size = (unsigned long long) size_low | ((unsigned long long) size_high << 32);
}
//------------------------------------------------------------------------------------------------------------




// APanel
//------------------------------------------------------------------------------------------------------------
APanel::APanel(unsigned short x_pos, unsigned short y_pos, unsigned short width, unsigned short height, CHAR_INFO* screen_buffer, unsigned short screen_width)
:X_Pos(x_pos), Y_Pos(y_pos), Width(width), Height(height), Screen_Buffer(screen_buffer), Screen_Width(screen_width)
{

}
//------------------------------------------------------------------------------------------------------------
void APanel::Draw()
{
	ASymbol symbol(L' ', 0x1b, L' ', L' ');
	SArea_Pos area_pos(X_Pos + 1, Y_Pos + 1, Screen_Width, Width - 2, Height - 2);
	Clear_Area(Screen_Buffer, area_pos, symbol);

	// 1. Horizontal lines
	// 1.1 Upper line
	{
		ASymbol symbol(L'═', 0x1b, L'╔', L'╗');
		X_Y_Pos position(X_Pos, Y_Pos, Screen_Width, Width - 2);
		Draw_Line_Horizontal(Screen_Buffer, position, symbol);
	}

	// 1.2 Lower line
	{
		ASymbol symbol(L'═', 0x1b, L'╚', L'╝');
		X_Y_Pos position(X_Pos, Y_Pos + Height - 1, Screen_Width, Width - 2);
		Draw_Line_Horizontal(Screen_Buffer, position, symbol);
	}

	// 2. Vertical lines
	// 2.1 Left line
	{
		ASymbol symbol(L'║', 0x1b, L'║', L'║');
		X_Y_Pos position(X_Pos, Y_Pos + 1, Screen_Width, Height - 4);
		Draw_Line_Vertical(Screen_Buffer, position, symbol);
	}

	// 2.2 Right line
	{
		ASymbol symbol(L'║', 0x1b, L'║', L'║');
		X_Y_Pos position(X_Pos + Width - 1, Y_Pos + 1, Screen_Width, Height - 4);
		Draw_Line_Vertical(Screen_Buffer, position, symbol);
	}

	// 3 Middle lines
	// 3.1 Middle horizontal line
	{
		ASymbol symbol(L'─', 0x1b, L'╟', L'╢');
		X_Y_Pos position(X_Pos, Y_Pos + Height - 3, Screen_Width, Width - 2);
		Draw_Line_Horizontal(Screen_Buffer, position, symbol);
	}

	// 3.2 Middle vertical line
	{
		ASymbol symbol(L'║', 0x1b, L'╦', L'╨');
		X_Y_Pos position(X_Pos + Width / 2, Y_Pos + 0, Screen_Width, Height - 4);
		Draw_Line_Vertical(Screen_Buffer, position, symbol);
	}


	//Show_Colors(Screen_Buffer, x_y_pos, symbol);
}
//------------------------------------------------------------------------------------------------------------
void APanel::Get_Directory_Files()
{
	HANDLE search_handle;
	WIN32_FIND_DATAW find_data{};

	search_handle = FindFirstFileW(L"*.*", &find_data);

	while (FindNextFileW(search_handle, &find_data))
	{
		AFile_Descriptor* file_descriptor = new AFile_Descriptor(find_data.dwFileAttributes, find_data.nFileSizeLow, find_data.nFileSizeHigh, find_data.cFileName);
	}
}
//------------------------------------------------------------------------------------------------------------