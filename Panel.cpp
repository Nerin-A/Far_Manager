#include "Panel.h"
// APanel
//------------------------------------------------------------------------------------------------------------
APanel::APanel(unsigned short x_pos, unsigned short y_pos, unsigned short width, unsigned short height, CHAR_INFO* screen_buffer, unsigned short screen_width)
	:X_Pos(x_pos), Y_Pos(y_pos), Width(width), Height(height), Screen_Buffer(screen_buffer), Screen_Width(screen_width)
{

}
void APanel::Draw()
{
   CHAR_INFO symbol{};
   symbol.Char.UnicodeChar = L'X';
   symbol.Attributes = 0x1b;
   XYPos x_y_pos(2, 1, Screen_Width, 10);

   //Draw_Line_Horizontal(Screen_Buffer, x_y_pos, symbol);
   Draw_Line_Vertical(Screen_Buffer, x_y_pos, symbol);

   //Show_Colors(Screen_Buffer, x_y_pos, symbol);
}
//------------------------------------------------------------------------------------------------------------