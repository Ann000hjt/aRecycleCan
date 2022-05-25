#pragma once
#include<iostream>
#include<windows.h>
#include<conio.h>
#include <time.h>
#include<string>

#include"drawAll.h"

using std::cout;
using std::endl;
#define LEVEL_0 0//��Ƭ->����ѹ����
#define LEVEL_1 1//����->��װ�ӹ���
#define LEVEL_2 2//��Ʒ->�����
#define LEVEL_3 3//���ɻ���Ʒ->�ɻ�������Ͱ


extern int windowsLenth;
extern int windowsWidth;
class Object
{

public:
    friend HDC DrawBmp(HDC hDC, HDC dcMEM, HBITMAP hBitmap, Object& object,int bmpLenth,int bmpWidth,bool isFirst);
    friend HDC DrawBmp(HDC hDC, HDC dcMEM, HBITMAP hBitmap, Can& can, int bmpLenth, int bmpWidth, bool isFirst,float interpolation);
    Object() {};
    virtual ~Object() {};
    virtual void move() = 0;
    virtual void draw() = 0;
    virtual void init() = 0;//��ʼ���������빹�캯�����ƣ����ǹ��캯��������ֱ�ӵ���
    virtual void changeState() = 0;//״̬�ı��⣬���磺�������������ˣ��ѷ����W�ĳ�D
    int getX() { return x; };
    int getY() { return y; };
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
protected:
    int x = windowsLenth/8;//���ĵ�X����
    int y = 4 * windowsWidth / 5;
};


class Can :public Object
{
public:
    Can();
    void move();
    //ÿ��move�궼Ҫdraw
    void draw();
    void changeState();
    void jump();
    int getv_y() { return v_y; };
    int getScore();
    int getLife();
    void init();
    char direction; //W��ʾ���� S��ʾ���� A��ʾ���� D��ʾ����
private:
    int life = 3;//�����޵�����
    int score = 0;//�Ե�������+1�����������̳ǹ���
    int level;
    int v_y;//y�����ϵ��ٶ�
    const int vAfterJump = -60;
};


//button�࣬���ְ�ť
class Button : public Object
{
public:
    Button() {};
    Button(int x, int y, int bmpLength, int bmpWidth);
    void draw();
    void changeState();
    void move();
    int getLength();
    int getWidth();
    void init();
private:
    int buttonLength = 0;
    int buttonWidth = 0;
};


//barrier�࣬�ϰ���
class Barrier : public Object
{
public:
    Barrier();
    void draw();
    void changeState();
    void move();
    void init();

private:
    int v_x = -16;
};


//coin�࣬����
class Coin :public Object
{
public:
    Coin();
    //��λһ������λ��
    void move();
    void draw();
    bool getEatenState();
    void changeState();
    void init();
private:
    //Coinһ��������������� ������ֵ�һ������һ������
    int v_y = 3;
    int v_x = -5;
    bool isEaten = false;
};


//title�࣬��־����
class Title:public Object
{
public:
    Title() {};
    Title(int x, int y,int bmpLength, int bmpWidth);
    void move() {};
    void draw() {};
    void init() {};
    void changeState() {};
private:
    int titleLength = 0;
    int titleWidth = 0;
};


//background�࣬����
class Background:public Object
{
public:
    Background() {};
    Background(int x, int y, int bmpLength, int bmpWidth);
    void move() {};
    void draw() {};
    void init() {};
    void changeState() {};
private:
    int backgroundLength = windowsLenth;
    int backgroundWidth = windowsWidth;
};