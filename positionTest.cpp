#include"positonTest.h"

//bmp图是一个矩形的时候，x是矩形长度的中点，y是矩形最小的一个点
//暂时认为还是原来的 都是中点 
bool isKickRect(int kick_x, int kick_y, int Rect_x,int Rect_y,int Rect_length ,int Rect_width,int narrow)
{
	if ((kick_x > Rect_x +narrow- Rect_length / 2) && (kick_x < Rect_x -narrow+ Rect_length / 2) && (kick_y > Rect_y +narrow- Rect_width / 2) && (kick_y < Rect_y -narrow+ Rect_width / 2))
		return true;
	return false;
}
bool isKickButton(int kick_x, int kick_y,Button button, int narrow)
{
	bool flag = false;
	if ((kick_x > button.getX() + narrow - button.getLength() / 2)
		&& (kick_x < button.getX() - narrow + button.getLength() / 2)
		&& (kick_y > button.getY() + narrow - button.getWidth() / 2)
		&& (kick_y < button.getY() - narrow + button.getWidth() / 2))
	{
		flag = true;
	}
	return flag;
}