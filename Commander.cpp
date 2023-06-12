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
	X_Y_Text_Pos key_position(X_Pos, Y_Pos, screen_width, 0x07);
	X_Y_Text_Pos name_position(X_Pos, Y_Pos, screen_width, 0xb0);

	Draw_Text(screen_buffer, key_position, Key);
	Draw_Text(screen_buffer, name_position, Name);
}
//------------------------------------------------------------------------------------------------------------




// AsCommander
//------------------------------------------------------------------------------------------------------------
AsCommander::~AsCommander()
{
	delete Left_Panel;
	delete Right_Panel;
	delete Screen_Buffer;
}
//------------------------------------------------------------------------------------------------------------
bool AsCommander::Init()
{
	SMALL_RECT srctWriteRect;
	int screen_buffer_size;

	// Get a handle to the STDOUT screen buffer to copy from and create a new screen buffer to copy to.
	Std_Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	Screen_Buffer_Handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);

	if (Std_Handle == INVALID_HANDLE_VALUE || Screen_Buffer_Handle == INVALID_HANDLE_VALUE)
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

	return true;
}
//------------------------------------------------------------------------------------------------------------
bool AsCommander::Draw()
{
	COORD screen_buffer_pos{};

	Left_Panel->Draw();
	Right_Panel->Draw();

	AMenu_Item menu_item(0, Screen_Buffer_Info.dwSize.Y - 1, L"1", L"Help", 8);
	menu_item.Draw(Screen_Buffer, Screen_Buffer_Info.dwSize.X);

	if (!WriteConsoleOutput(Screen_Buffer_Handle, Screen_Buffer, Screen_Buffer_Info.dwSize, screen_buffer_pos, &Screen_Buffer_Info.srWindow))
	{
		printf("WriteConsoleOutput failed - (%d)\n", GetLastError());
		return false;
	}

	Sleep(100 * 1000);

	// Restore the original active screen buffer.
	if (!SetConsoleActiveScreenBuffer(Std_Handle))
	{
		printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
		return false;
	}

	return true;
}
//------------------------------------------------------------------------------------------------------------