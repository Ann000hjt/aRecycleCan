#include"positonTest.h"

extern double correctX;
extern double correctY;
//У��ϵ��ֻ������ײ����ʱ����Ҫ�õ�������ʱ������궼ȡ�ϴ�ֵ(ȫ��)
//�������Ϊ�ϴ�ֵΪ����ֵ������ϵ��֮��õ���Сֵ��������Ļ�ϵ�ʵ��ֵ

//bmpͼ��һ�����ε�ʱ�������Ǿ��ε����Ͻ�
bool isKickRect(int kick_x, int kick_y, int Rect_x,int Rect_y,int Rect_length ,int Rect_width,int narrow)
{
	if ((kick_x > Rect_x +narrow- Rect_length / 2) && (kick_x < Rect_x -narrow+ Rect_length / 2) && (kick_y > Rect_y +narrow- Rect_width / 2) && (kick_y < Rect_y -narrow+ Rect_width / 2))
		return true;
	return false;
}
bool isKickButton(int kick_x, int kick_y,Button button, int narrow)
{
	//��ť�������ǰ�ť�����Ͻ�
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
	//can180*320  coin����120*80  coin������100*100
	//can�ģ��ұ߻����������&&���ϱ߻��±�������
	int canLenth = 180;
	int canWidth = 320;
	int coinLenth = 120;
	int coinWidth = 80;
	if (coin.getType() == 2)
	{
		coinLenth = 100;
		coinWidth = 100;
	}

	//��ײ������Ҷ�����ϵ��������
	//�����ɹ������޾ͼ���ұ� û�ɹ��ͼ����ߣ�����������������ͼ������ ��֮�������
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
//Բ����ײ���(�����)����Ҫ�� �������������
bool isBarrierCrush(Can& can, Barrier& barrier)
{
	int canLenth = 180;
	int canWidth = 320;
	//�е��Ѷ㣬�ҰѼ�ⷶΧ��С��
	int barrierLenth = 100;
	int barrierWidth = 100;

	//��ײ������Ҷ�����ϵ��������
	//�����ɹ������޾ͼ���ұ� û�ɹ��ͼ����ߣ�����������������ͼ������ ��֮�������
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