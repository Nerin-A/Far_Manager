extern "C" int Make_Sum(int value_1, int value_2);

#include <windows.h>
#include <stdio.h>

int main(void)
{
   HANDLE std_handle, screen_buffer_handle;
   SMALL_RECT srctReadRect;
   SMALL_RECT srctWriteRect;
   CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info{};
   //CHAR_INFO chiBuffer[160]; // [2][80];
   CHAR_INFO* screen_buffer;
   COORD coordBufSize;
   COORD coordBufCoord;
   BOOL fSuccess;

   // Get a handle to the STDOUT screen buffer to copy from and create a new screen buffer to copy to.
   std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
   screen_buffer_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE, 0,CONSOLE_TEXTMODE_BUFFER, 0);

   if (std_handle == INVALID_HANDLE_VALUE || screen_buffer_handle == INVALID_HANDLE_VALUE)
   {
      printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
      return 1;
   }

   // Make the new screen buffer the active screen buffer.

   if (!SetConsoleActiveScreenBuffer(screen_buffer_handle))
   {
      printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
      return 1;
   }   
   
   if (! GetConsoleScreenBufferInfo(screen_buffer_handle, &screen_buffer_info))
   {
      printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
      return 1;
   }

   screen_buffer = new CHAR_INFO[(int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y];

   // Set the source rectangle.
   srctReadRect.Top = 0;    // top left: row 0, col 0
   srctReadRect.Left = 0;
   srctReadRect.Bottom = 1; // bot. right: row 1, col 79
   srctReadRect.Right = 79;

   // The temporary buffer size is 2 rows x 80 columns.
   coordBufSize.Y = 2;
   coordBufSize.X = 80;

   // The top left destination cell of the temporary buffer is row 0, col 0.
   coordBufCoord.X = 0;
   coordBufCoord.Y = 0;

   // Set the destination rectangle.

   srctWriteRect.Top = 10;    // top lt: row 10, col 0
   srctWriteRect.Left = 0;
   srctWriteRect.Bottom = 11; // bot. rt: row 11, col 79
   srctWriteRect.Right = 79;

   // Copy from the temporary buffer to the new screen buffer.

   screen_buffer[0].Char.UnicodeChar = L'X';
   screen_buffer[0].Attributes = 0x50;

   fSuccess = WriteConsoleOutput(
      screen_buffer_handle, // screen buffer to write to
      screen_buffer,        // buffer to copy from
      coordBufSize,     // col-row size of chiBuffer
      coordBufCoord,    // top left src cell in chiBuffer
      &srctWriteRect);  // dest. screen buffer rectangle
   if (!fSuccess)
   {
      printf("WriteConsoleOutput failed - (%d)\n", GetLastError());
      return 1;
   }
   Sleep(5000);

   // Restore the original active screen buffer.

   if (!SetConsoleActiveScreenBuffer(std_handle))
   {
      printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
      return 1;
   }

   return 0;
}