#pragma once
#include<iostream>
#include<windows.h>
#include<conio.h>
#include <time.h>
#include<string>

#include"drawAll.h"

using std::cout;
using std::endl;
#define LEVEL_0 0//铝片->重量压型器
#define LEVEL_1 1//铝罐->包装加工线
#define LEVEL_2 2//完品->购物架
#define LEVEL_3 3//不可回收品->可回收垃圾桶


extern int windowsLenth1;
extern int windowsWidth1;

class Object
{

public:
    friend HDC DrawBmp(HDC hDC, HDC dcMEM, HBITMAP hBitmap, Object& object,int bmpLenth,int bmpWidth,bool isFirst);
    friend HDC DrawBmp(HDC hDC, HDC dcMEM, HBITMAP hBitmap, Can& can, int bmpLenth, int bmpWidth, bool isFirst,float interpolation);
    Object() {};
    virtual ~Object() {};
    virtual void move() = 0;
    virtual void init() = 0;//初始化函数，与构造函数类似，但是构造函数不可以直接调用
    virtual void changeState() = 0;//状态改变检测，例如：如果起跳后落地了，把方向从W改成D
    int getX() { return x; };
    int getY() { return y; };
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
protected:
    int x = windowsLenth1/8;//中心的X坐标
    int y = 4 * windowsWidth1 / 5;
};


class Can :public Object
{
public:
    Can();
    void move();
    void changeState();
    void jump();
    int getv_y() { return v_y; };
    void plusScore();
    int getScore();
    void cutLife();
    void plusLife();
    int getLife();

    int getLength();
    int getWidth();
    void init();
    char direction; //W表示向上 S表示向下 A表示向左 D表示向右
private:
    int canLength = 150;
    int canWidth = 250;
    int life = 3;//易拉罐的生命
    int score = 0;//吃到拉环就+1，可以用于商城购物
    int level;
    int v_y;//y方向上的速度
    const int vAfterJump = -40;
};


//button类，各种按钮
class Button : public Object
{
public:
    Button() {};
    Button(int x, int y, int bmpLength, int bmpWidth);
    void changeState() {};
    void move() {};
    int getLength();
    int getWidth();
    void init() {};
private:
    int buttonLength = 0;
    int buttonWidth = 0;
};


//barrier类，障碍物
class Barrier : public Object
{
public:
    Barrier() {};
    Barrier(int bmpLength, int bmpWidth);
    void changeState();
    void Crush();
    void move();
    int getLength();
    int getWidth();
    void init();

private:
    int v_x = -15;
    int barrierLength;
    int barrierWidth;
    bool isCrush = false;
};


//coin类，道具：拉环、加生命值
class Coin :public Object
{
public:
    Coin() {};
    Coin(int Cointype);
    //定位一个拉环位置
    void move();
    bool getEatenState();
    void Eaten();
    void changeState();
    void init();
    int getType();
private:
    //Coin一定概率下随机出现 随机出现的一个就是一个对象
    int v_y = 3;
    int v_x = -5;
    bool isEaten = false;
    int type = 1;//1是拉环，2是加生命值
};


//title类，标志标题
class Title:public Object
{
public:
    Title() {};
    Title(int x, int y,int bmpLength, int bmpWidth);
    void move() {};
    void init() {};
    void changeState() {};
private:
    int titleLength = 0;
    int titleWidth = 0;
};


//background类，背景
class Background:public Object
{
public:
    Background() {};
    Background(int x, int y, int bmpLength, int bmpWidth);
    void move() {};
    void init() {};
    void changeState() {};
private:
    int backgroundLength = windowsLenth1;
    int backgroundWidth = windowsWidth1;
};