#include "Main.h"

// AsCommander
//------------------------------------------------------------------------------------------------------------
AsCommander::~AsCommander()
{
	delete Left_Panel;
	delete Right_Panel;
}
//------------------------------------------------------------------------------------------------------------
void AsCommander::Init()
{
	SMALL_RECT srctWriteRect;
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info{};
	CHAR_INFO* screen_buffer;
	COORD screen_buffer_pos{};
	int screen_buffer_size;

	// Get a handle to the STDOUT screen buffer to copy from and create a new screen buffer to copy to.
	Std_Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	Screen_Buffer_Handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);

	if (Std_Handle == INVALID_HANDLE_VALUE || Screen_Buffer_Handle == INVALID_HANDLE_VALUE)
	{
		printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
		return 1;
	}

	// Make the new screen buffer the active screen buffer.
	if (!SetConsoleActiveScreenBuffer(Screen_Buffer_Handle))
	{
		printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
		return 1;
	}

	if (!GetConsoleScreenBufferInfo(Screen_Buffer_Handle, &screen_buffer_info))
	{
		printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
		return 1;
	}

	screen_buffer_size = (int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y;
	screen_buffer = new CHAR_INFO[screen_buffer_size];
	memset(screen_buffer, 0, screen_buffer_size * sizeof(CHAR_INFO));

	// Set the destination rectangle.

	srctWriteRect.Top = 10;    // top lt: row 10, col 0
	srctWriteRect.Left = 0;
	srctWriteRect.Bottom = 11; // bot. rt: row 11, col 79
	srctWriteRect.Right = 79;

	short half_width = screen_buffer_info.dwSize.X / 2;
	Left_Panel = new APanel (0, 0, half_width, screen_buffer_info.dwSize.Y - 2, screen_buffer, screen_buffer_info.dwSize.X);
	Right_Panel = new APanel (half_width, 0, half_width, screen_buffer_info.dwSize.Y - 2, screen_buffer, screen_buffer_info.dwSize.X);
}
//------------------------------------------------------------------------------------------------------------
void AsCommander::Draw()
{
	Left_Panel->Draw();
	Right_Panel->Draw();

	if (!WriteConsoleOutput(Screen_Buffer_Handle, screen_buffer, screen_buffer_info.dwSize, screen_buffer_pos, &screen_buffer_info.srWindow))
	{
		printf("WriteConsoleOutput failed - (%d)\n", GetLastError());
		return 1;
	}

	Sleep(100 * 1000);

	// Restore the original active screen buffer.

	if (!SetConsoleActiveScreenBuffer(Std_Handle))
	{
		printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
		return 1;
	}
}
//------------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------------
int main(void)
{
	AsCommander Commander;

	if (!Commander.Init())
		return -1;

	if (!Commander.Draw())
		return -1;

	return 0;
}
//------------------------------------------------------------------------------------------------------------