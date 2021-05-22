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
//圆形碰撞检测
bool isBarrierCrush(Can& can, Barrier& barrier)
{
	int circleX = barrier.getX() + barrier.getLength() / 2;//障碍物中心的X坐标
	int radius = barrier.getLength() / 2;//障碍物（圆）的半径
	int circleY = barrier.getY() + barrier.getWidth() / 2;//障碍物中心的Y坐标

	int RecL = can.getX();//矩形左坐标
	int RecT = can.getY();//矩形上坐标
	int RecR = can.getX()+can.getLength();//矩形右坐标
	int RecB = can.getY()+can.getWidth();//矩形下坐标

	//判断矩形离圆最近的点的X坐标
	int closeX;
	if (RecR < circleX)//矩形在圆形左边DO
	{
		closeX = RecR;
	}
	else if (RecL > circleX)//矩形在圆形右边OD
	{
		closeX = RecL;
	}
	else//有重合部分，或者矩形在圆形上下  D
	{                                   //O
		closeX = circleX;
	}
	//判断矩形离圆最近的点的Y坐标
	int closeY;
	if (RecB < circleY)//矩形在圆形上边
	{
		closeY = RecB;
	}
	else if (RecT > circleY)//矩形在圆形下边
	{
		closeY = RecT;
	}
	else//有重合部分，或者矩形在圆形左右
	{                                   
		closeY = circleY;
	}
	int RFang = radius * radius;

	int DFang = pow(closeX - circleX, 2) + pow(closeY - circleY, 2);

	bool isCrush = false;
	if (DFang <= RFang)
	{
		isCrush = true;
	}
	return isCrush;
}