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