#include"positonTest.h"

//bmpͼ��һ�����ε�ʱ��x�Ǿ��γ��ȵ��е㣬y�Ǿ�����С��һ����
//��ʱ��Ϊ����ԭ���� �����е� 
bool isKickRect(int kick_x, int kick_y, int Rect_x,int Rect_y,int Rect_length ,int Rect_width,int narrow)
{
	if ((kick_x > Rect_x +narrow- Rect_length / 2) && (kick_x < Rect_x -narrow+ Rect_length / 2) && (kick_y > Rect_y +narrow- Rect_width / 2) && (kick_y < Rect_y -narrow+ Rect_width / 2))
		return true;
	return false;
}