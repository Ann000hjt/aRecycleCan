#pragma once
#include"Object.h"
bool isKickRect(int kick_x, int kick_y, int Rect_x, int Rect_y, int Rect_length, int Rect_width, int narrow);
//��Ϊ�����δ�С�밴ť��Сһ����ʱ�� �������ΧҲ����ͨ������� �����Ҽ���һ��narrow��������С��ֵ
//Rect_x��Rect_y�Ǿ��ε�����λ��
bool isKickButton(int kick_x, int kick_y, Button button, int narrow);
bool isCoinEaten(Can& can, Coin& coin);
bool isBarrierCrush(Can& can, Barrier& barrier);