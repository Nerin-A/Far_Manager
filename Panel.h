﻿#pragma once

#include <windows.h>
#include "Asm_Tools_Interface.h"
#include <string>
#include <vector>

//------------------------------------------------------------------------------------------------------------
class AFile_Descriptor
{
public:
	AFile_Descriptor(unsigned int attributes, unsigned int size_low, unsigned int size_high, wchar_t* file_name);

	unsigned int Attributes;
	unsigned long long File_Size;
	std::wstring Filename;
};
//------------------------------------------------------------------------------------------------------------
class APanel
{
public:
	APanel(unsigned short x_pos, unsigned short y_pos, unsigned short width, unsigned short height, CHAR_INFO* screen_buffer, unsigned short screen_width);

	void Draw();
	void Get_Directory_Files(const std::wstring &current_directory);
	void Move_Highlight(bool move_up);
	void On_Enter();

private:
	void Draw_Panel();
	void Draw_Files();
	void Draw_A_Single_File(AFile_Descriptor* file_descriptor, unsigned short x_offset, unsigned short y_offset, unsigned short bg_attribute);
	void Draw_Highlihgt();

	unsigned short X_Pos, Y_Pos;
	unsigned short Width, Height;
	unsigned short Screen_Width;
	CHAR_INFO* Screen_Buffer;

	unsigned short Current_File_Index;
	unsigned short Highlihgt_X_Offset;
	unsigned short Highlihgt_Y_Offset;

	std::wstring Current_Directory;
	std::vector<AFile_Descriptor*> Files;
};
//------------------------------------------------------------------------------------------------------------