#include "Commander.h"

// AMenu_Item
//------------------------------------------------------------------------------------------------------------
AMenu_Item::AMenu_Item(unsigned short x_pos, unsigned short y_pos, const wchar_t* key, const wchar_t* name, unsigned short length)
	:X_Pos(x_pos), Y_Pos(y_pos), Key(key), Name(name), Length(length)
{
}
//------------------------------------------------------------------------------------------------------------
void AMenu_Item::Draw(CHAR_INFO* screen_buffer, unsigned short screen_width)
{
	unsigned char key_string_length;

	X_Y_Text_Pos key_position(X_Pos, Y_Pos, screen_width, 0x07);
	key_string_length = Draw_Text(screen_buffer, key_position, Key);

	X_Y_Text_Pos name_position(X_Pos + key_string_length, Y_Pos, screen_width, 0xb0);
	Draw_Limited_Text(screen_buffer, name_position, Name, Length);
}
//------------------------------------------------------------------------------------------------------------




// AsCommander
//------------------------------------------------------------------------------------------------------------
AsCommander::~AsCommander()
{
	// Restore the original active screen buffer.
	if (!SetConsoleActiveScreenBuffer(Std_Output_Handle))
		printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());

	delete Left_Panel;
	delete Right_Panel;
	delete Screen_Buffer;
}
//------------------------------------------------------------------------------------------------------------
bool AsCommander::Init()
{
	SMALL_RECT srctWriteRect;
	int screen_buffer_size;

	Std_Input_Handle = GetStdHandle(STD_INPUT_HANDLE);
	Std_Output_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

	Screen_Buffer_Handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);

	if (Std_Input_Handle == INVALID_HANDLE_VALUE || Std_Output_Handle == INVALID_HANDLE_VALUE || Screen_Buffer_Handle == INVALID_HANDLE_VALUE)
	{
		printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
		return false;
	}

	// Make the new screen buffer the active screen buffer.
	if (!SetConsoleActiveScreenBuffer(Screen_Buffer_Handle))
	{
		printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
		return false;
	}

	if (!GetConsoleScreenBufferInfo(Screen_Buffer_Handle, &Screen_Buffer_Info))
	{
		printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
		return false;
	}

	screen_buffer_size = (int)Screen_Buffer_Info.dwSize.X * (int)Screen_Buffer_Info.dwSize.Y;
	Screen_Buffer = new CHAR_INFO[screen_buffer_size];
	memset(Screen_Buffer, 0, screen_buffer_size * sizeof(CHAR_INFO));

	// Set the destination rectangle.

	srctWriteRect.Top = 10;    // top lt: row 10, col 0
	srctWriteRect.Left = 0;
	srctWriteRect.Bottom = 11; // bot. rt: row 11, col 79
	srctWriteRect.Right = 79;

	short half_width = Screen_Buffer_Info.dwSize.X / 2;
	Left_Panel = new APanel(0, 0, half_width, Screen_Buffer_Info.dwSize.Y - 2, Screen_Buffer, Screen_Buffer_Info.dwSize.X);
	Right_Panel = new APanel(half_width, 0, half_width, Screen_Buffer_Info.dwSize.Y - 2, Screen_Buffer, Screen_Buffer_Info.dwSize.X);

	Build_Menu();

	Left_Panel->Get_Directory_Files();

	return true;
}
//------------------------------------------------------------------------------------------------------------
void AsCommander::Run()
{
	unsigned long records_count;
	INPUT_RECORD input_record[128];

	Have_To_Redraw = true;
	Can_Run = true;

	while (Can_Run)
	{
		if (PeekConsoleInput (Std_Input_Handle, input_record, 128, &records_count))
		{
			if (ReadConsoleInput(Std_Input_Handle, input_record, 1, &records_count))
			{
				if (records_count != 0)
				{
					if (input_record[0].EventType == KEY_EVENT)
					{
						if (input_record[0].Event.KeyEvent.wVirtualKeyCode == VK_F10)
							Can_Run = false;

						if (input_record[0].Event.KeyEvent.wVirtualKeyCode == VK_UP)
							int zzz = 0;

						if (input_record[0].Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
							int zzz = 0;
					}
				}
			}
		}

		if (Have_To_Redraw)
		{
			if (!Draw())
				return;

			Have_To_Redraw = false;
		}
	}
}
//------------------------------------------------------------------------------------------------------------
bool AsCommander::Draw()
{
	int i;
	COORD screen_buffer_pos{};

	Left_Panel->Draw();
	Right_Panel->Draw();

	for (i = 0; i < 10; i++)
	{
		if (Menu_Items[i] != 0)
			Menu_Items[i]->Draw(Screen_Buffer, Screen_Buffer_Info.dwSize.X);
	}

	if (!WriteConsoleOutput(Screen_Buffer_Handle, Screen_Buffer, Screen_Buffer_Info.dwSize, screen_buffer_pos, &Screen_Buffer_Info.srWindow))
	{
		printf("WriteConsoleOutput failed - (%d)\n", GetLastError());
		return false;
	}

	Sleep(100 * 1000);

	return true;
}
//------------------------------------------------------------------------------------------------------------
void AsCommander::Add_Next_Menu_Item(unsigned char &index, short &x_pos, short x_step, const wchar_t* key, const wchar_t* name)
{
	Menu_Items[index++] = new AMenu_Item(x_pos, Screen_Buffer_Info.dwSize.Y - 1, key, name, 11);
	x_pos += x_step;

	if (index == 2)
		--x_pos;
}
//------------------------------------------------------------------------------------------------------------
void AsCommander::Build_Menu()
{
	unsigned char index = 0;
	short x_pos = 0;
	short x_step = Screen_Buffer_Info.dwSize.X / 10;

	Add_Next_Menu_Item(index, x_pos, x_step, L" 1",  L"Help");
	Add_Next_Menu_Item(index, x_pos, x_step, L" 2",  L"UserMenu");
	Add_Next_Menu_Item(index, x_pos, x_step, L" 3",  L"View");
	Add_Next_Menu_Item(index, x_pos, x_step, L" 4",  L"Edit");
	Add_Next_Menu_Item(index, x_pos, x_step, L" 5",  L"Copy");
	Add_Next_Menu_Item(index, x_pos, x_step, L" 6",  L"RenMov");
	Add_Next_Menu_Item(index, x_pos, x_step, L" 7",  L"MkDir");
	Add_Next_Menu_Item(index, x_pos, x_step, L" 8",  L"Delete");
	Add_Next_Menu_Item(index, x_pos, x_step, L" 9",  L"Config");
	Add_Next_Menu_Item(index, x_pos, x_step, L" 10", L"Quit");
}
//------------------------------------------------------------------------------------------------------------