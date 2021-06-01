#include<fstream>//ifs
#include<iostream>

#include"Object.h"
#define GAME_SAVE "gameData.txt"
using namespace std;

void read_save(Can& can)
{
	ifstream ifs;
	ifs.open(GAME_SAVE, ios::in);
	//文件不存在情况
	if (!ifs.is_open())
	{
		//初始化所有要存档的数据
		can.score = 0;//初始化拉环
		ifs.close();
		return;
	}
	
	//char ch;
	//ifs >> ch;//读第一个字符
	////文件存在但为空情况
	//if (ifs.eof())
	//{
	//	can.score = 0;//初始化拉环
	//	ifs.close();
	//	return;
	//}

	//文件存在并且有数据情况
	//读取所有存档的数据
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
	//ios::trunc  覆盖  更新score

	ofs << can.score << endl;

	ofs.close();
}