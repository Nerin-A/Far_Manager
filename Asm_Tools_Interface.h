#pragma once

#include "Common.h"

//------------------------------------------------------------------------------------------------------------
extern "C" int Make_Sum(int value_1, int value_2);
extern "C" void Draw_Line_Horizontal(CHAR_INFO * screen_buffer, X_Y_Pos x_y_pos, ASymbol symbol);
extern "C" void Draw_Line_Vertical(CHAR_INFO * screen_buffer, X_Y_Pos x_y_pos, ASymbol symbol);
extern "C" void Show_Colors(CHAR_INFO * screen_buffer, X_Y_Pos x_y_pos, CHAR_INFO symbol);
extern "C" void Clear_Area(CHAR_INFO * screen_buffer, SArea_Pos area_pos, ASymbol symbol);
extern "C" void Draw_Text(CHAR_INFO* screen_buffer, X_Y_Text_Pos position, const char* string);

//------------------------------------------------------------------------------------------------------------