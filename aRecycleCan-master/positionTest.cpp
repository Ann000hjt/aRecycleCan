#include"positonTest.h"

extern double correctX;
extern double correctY;
//校正系数只有在碰撞检测的时候需要用到，其他时候的坐标都取较大值(全屏)
//可以理解为较大值为理想值，乘以系数之后得到较小值，即在屏幕上的实际值

//bmp图是一个矩形的时候，坐标是矩形的左上角
bool isKickRect(int kick_x, int kick_y, int Rect_x,int Rect_y,int Rect_length ,int Rect_width,int narrow)
{
	if ((kick_x > Rect_x +narrow- Rect_length / 2) && (kick_x < Rect_x -narrow+ Rect_length / 2) && (kick_y > Rect_y +narrow- Rect_width / 2) && (kick_y < Rect_y -narrow+ Rect_width / 2))
		return true;
	return false;
}
bool isKickButton(int kick_x, int kick_y,Button button, int narrow)
{
	//按钮的坐标是按钮的左上角
	bool flag = false;
	if ((kick_x > button.getX()*correctX + narrow )
		&& (kick_x < button.getX() * correctX - narrow + button.getLength() * correctX)
		&& (kick_y > button.getY() * correctY + narrow )
		&& (kick_y < button.getY() * correctY - narrow + button.getWidth() * correctY))
	{
		flag = true;
	}
	return flag;
}
bool isCoinEaten(Can& can, Coin& coin)
{
	//can180*320  coin拉环120*80  coin加生命100*100
	//can的（右边或左边碰到）&&（上边或下边碰到）
	int canLenth = 180;
	int canWidth = 320;
	int coinLenth = 120;
	int coinWidth = 80;
	if (coin.getType() == 2)
	{
		coinLenth = 100;
		coinWidth = 100;
	}

	//碰撞检测左右都除以系数相消了
	//拉环飞过易拉罐就检测右边 没飞过就检测左边；拉环在易拉罐下面就检测下面 反之检测上面
	if (can.getX()+ canLenth <= coin.getX() ?
		can.getX() + canLenth  >= coin.getX() : can.getX() <= coin.getX() + coinLenth )
	{
		if (can.getY() +canWidth<= coin.getY() ?
			can.getY() + canWidth >= coin.getY()  : can.getY()<= coin.getY() + coinWidth )
			return true;
		else
			return false;
	}
	else
		return false;
}
//圆形碰撞检测(搬代码)，还要改 先用上面代替了
bool isBarrierCrush(Can& can, Barrier& barrier)
{
	int canLenth = 180;
	int canWidth = 320;
	//有点难躲，我把检测范围减小了
	int barrierLenth = 100;
	int barrierWidth = 100;

	//碰撞检测左右都除以系数相消了
	//拉环飞过易拉罐就检测右边 没飞过就检测左边；拉环在易拉罐下面就检测下面 反之检测上面
	if (can.getX() + canLenth <= barrier.getX() ?
		can.getX() + canLenth >= barrier.getX() : can.getX() <= barrier.getX() + barrierLenth)
	{
		if (can.getY() + canWidth <= barrier.getY() ?
			can.getY() + canWidth >= barrier.getY() : can.getY() <= barrier.getY() + barrierWidth)
			return true;
		else
			return false;
	}
	else
		return false;
}