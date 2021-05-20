#include"positonTest.h"

//bmpͼ��һ�����ε�ʱ��x�Ǿ��γ��ȵ��е㣬y�Ǿ�����С��һ����
//��ʱ��Ϊ����ԭ���� �����е� 
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
	//can�ģ��ұ߻����������&&���ϱ߻��±�������
	
	//����û�зɹ������� ����ұ�
	if (can.getX() <= coin.getX() && can.getX() + 90 >= coin.getX() - 60
		&& (can.getY() - 160 >= coin.getY() + 40 || can.getY() + 160 <= coin.getY() - 40))
		return true;
	//�����ɹ��������� ������
	else if (can.getX()>coin.getX()&& can.getX() - 90 <= coin.getX() + 60
		&& (can.getY() - 160 >= coin.getY() + 40 || can.getY() + 160 <= coin.getY() - 40))
		return true;
	else 
		return false;
}
//Բ����ײ���
bool isBarrierCrush(Can& can, Barrier& barrier)
{
	return false;
}