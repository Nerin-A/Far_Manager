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
	Draw_Panel();
	Draw_Files();
	Draw_Highlihgt();
}
//------------------------------------------------------------------------------------------------------------
void APanel::Get_Directory_Files(const std::wstring &current_directory)
{
	HANDLE search_handle;
	WIN32_FIND_DATAW find_data{};

	for (auto* file : Files)
		delete file;

	Files.erase(Files.begin(), Files.end());

	Current_Directory = current_directory;

	search_handle = FindFirstFileW((current_directory + L"\\*.*").c_str(), &find_data);

	while (FindNextFileW(search_handle, &find_data))
	{
		AFile_Descriptor* file_descriptor = new AFile_Descriptor(find_data.dwFileAttributes, find_data.nFileSizeLow, find_data.nFileSizeHigh, find_data.cFileName);
		Files.push_back(file_descriptor);
	}

	Current_File_Index = 0;
	Highlihgt_X_Offset = 0;
	Highlihgt_Y_Offset = 0;
}
//------------------------------------------------------------------------------------------------------------
void APanel::Move_Highlight(bool move_up)
{
	if (move_up)
	{
		if (Current_File_Index > 0)
		{
			--Current_File_Index;
			--Highlihgt_Y_Offset;
		}
	}
	else
	{
		if (Current_File_Index + (unsigned short)1 < Files.size())
		{
			++Current_File_Index;
			++Highlihgt_Y_Offset;
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void APanel::On_Enter()
{
	AFile_Descriptor* file_descriptor = Files[Current_File_Index];

	if (file_descriptor->Attributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		if (file_descriptor->Filename == L"..")
		{ // Exit to the previous directory

		}
		else
		{ // We enter the selected directory

			std::wstring new_current_directory = Current_Directory + L"\\" + file_descriptor->Filename;

			Get_Directory_Files(new_current_directory);
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void APanel::Draw_Panel()
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
void APanel::Draw_Files()
{
	unsigned short x_offset = 0;
	unsigned short y_offset = 0;

	for (auto* file : Files)
	{
		Draw_A_Single_File(file, x_offset, y_offset, 0x10);

		++y_offset;

		if (y_offset >= Height - 5)
		{ // Filled the left column with filenames
			if (x_offset == 0)
			{
				x_offset += Width / 2;
				y_offset = 2;
			}
			else
				break; // We only have 2 columns with filenames
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void APanel::Draw_A_Single_File(AFile_Descriptor* file_descriptor, unsigned short x_offset, unsigned short y_offset, unsigned short bg_attribute)
{
	unsigned short attributes;

	if (file_descriptor->Attributes & FILE_ATTRIBUTE_DIRECTORY)
		attributes = bg_attribute | 0x0f;
	else
		attributes = bg_attribute | 0x0b;

	X_Y_Text_Pos position(X_Pos + x_offset + 1, Y_Pos + y_offset + 2, Screen_Width, attributes);
	Draw_Limited_Text(Screen_Buffer, position, file_descriptor->Filename.c_str(), Width / 2 - 1);
}
//------------------------------------------------------------------------------------------------------------
void APanel::Draw_Highlihgt()
{
	AFile_Descriptor* file_descriptor;
	
	if (Current_File_Index >= Files.size())
		return;

	file_descriptor = Files[Current_File_Index];

	Draw_A_Single_File(file_descriptor, Highlihgt_X_Offset, Highlihgt_Y_Offset, 0xb0);
}
//------------------------------------------------------------------------------------------------------------