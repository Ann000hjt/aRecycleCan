#pragma once
#pragma once
#include<iostream>
#include<windows.h>
#include<conio.h>
#include <time.h>
#include<string>
using std::cout;
using std::endl;
#define LEVEL_0 0//��Ƭ->����ѹ����
#define LEVEL_1 1//����->��װ�ӹ���
#define LEVEL_2 2//��Ʒ->�����
#define LEVEL_3 3//���ɻ���Ʒ->�ɻ�������Ͱ

class Object
{
public:
    Object() {};
    virtual ~Object() {};
    virtual void move() = 0;
    virtual void draw() = 0;

protected:
    int x = 20;
    int y = 20;
};
class Can :public Object
{
public:
    Can();
    void move();
    //ÿ��move�궼Ҫdraw
    void draw();
private:
    int level;
    int v_x;//x�����ϵ��ٶ�
    int v_y;//y�����ϵ��ٶ�
    char direction;
    //W��ʾ���� S��ʾ���� A��ʾ���� D��ʾ����
    int score;//�÷�
};
//class Coin :public Object
//{
//public:
//    Coin();
//    //��λһ������λ��
//    void move();
//    void draw();
//private:
//    //Coinһ��������������� ������ֵ�һ������һ������
//    bool isEaten;
//};