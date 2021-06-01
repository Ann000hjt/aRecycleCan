#include<fstream>//ifs
#include<iostream>

#include"Object.h"
#define GAME_SAVE "gameData.txt"
using namespace std;

void read_save(Can& can)
{
	ifstream ifs;
	ifs.open(GAME_SAVE, ios::in);
	//�ļ����������
	if (!ifs.is_open())
	{
		//��ʼ������Ҫ�浵������
		can.score = 0;//��ʼ������
		ifs.close();
		return;
	}
	
	//char ch;
	//ifs >> ch;//����һ���ַ�
	////�ļ����ڵ�Ϊ�����
	//if (ifs.eof())
	//{
	//	can.score = 0;//��ʼ������
	//	ifs.close();
	//	return;
	//}

	//�ļ����ڲ������������
	//��ȡ���д浵������
	int num;

	while (ifs >> num)
	{
		can.score = num;
		return;
	}
}

void save_data(Can& can)
{
	ofstream ofs;
	ofs.open(GAME_SAVE, ios::trunc);
	//ios::trunc  ����  ����score

	ofs << can.score << endl;

	ofs.close();
}