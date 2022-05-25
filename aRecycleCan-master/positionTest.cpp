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
bool isCoinEaten(Can& can, Coin& coin)
{
	//can180*320  coin120*80
	//can的（右边或左边碰到）&&（上边或下边碰到）
	
	//拉环没有飞过易拉罐 检测右边
	if (can.getX() <= coin.getX() && can.getX() + 90 >= coin.getX() - 60
		&& (can.getY() - 160 >= coin.getY() + 40 || can.getY() + 160 <= coin.getY() - 40))
		return true;
	//拉环飞过了易拉罐 检测左边
	else if (can.getX()>coin.getX()&& can.getX() - 90 <= coin.getX() + 60
		&& (can.getY() - 160 >= coin.getY() + 40 || can.getY() + 160 <= coin.getY() - 40))
		return true;
	else 
		return false;
}
//圆形碰撞检测
bool isBarrierCrush(Can& can, Barrier& barrier)
{
	return false;
}