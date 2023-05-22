#include <windows.h>
#include <stdio.h>
//------------------------------------------------------------------------------------------------------------
struct XYPos
{
   XYPos(unsigned short x_pos, unsigned short y_pos, unsigned short screen_width, unsigned short length)
      : X_Pos(x_pos), Y_Pos(y_pos), Screen_Width(screen_width), Length(length)
   {
   }

   unsigned short X_Pos;
   unsigned short Y_Pos;
   unsigned short Screen_Width;
   unsigned short Length;
};
//------------------------------------------------------------------------------------------------------------
extern "C" int Make_Sum(int value_1, int value_2);
extern "C" void Draw_Line_Horizontal(CHAR_INFO * screen_buffer, XYPos x_y_pos, CHAR_INFO symbol);
extern "C" void Draw_Line_Vertical(CHAR_INFO * screen_buffer, XYPos x_y_pos, CHAR_INFO symbol);
extern "C" void Show_Colors(CHAR_INFO * screen_buffer, XYPos x_y_pos, CHAR_INFO symbol);
//------------------------------------------------------------------------------------------------------------
class APanel 
{
public:
   APanel(unsigned short x_pos, unsigned short y_pos, unsigned short width, unsigned short height);

   void Draw();

   unsigned short X_Pos, Y_Pos;
   unsigned short Width, Height;
};
//------------------------------------------------------------------------------------------------------------