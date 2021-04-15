#pragma once
#pragma once
#include<iostream>
#include<windows.h>
#include<conio.h>
#include <time.h>
#include<string>
using std::cout;
using std::endl;
#define LEVEL_0 0//铝片->重量压型器
#define LEVEL_1 1//铝罐->包装加工线
#define LEVEL_2 2//完品->购物架
#define LEVEL_3 3//不可回收品->可回收垃圾桶




extern int windowsLenth;
extern int windowsWidth;
class Object
{
public:
    Object() {};
    virtual ~Object() {};
    virtual void move() = 0;
    virtual void draw() = 0;
    virtual void changeState() = 0;//状态改变检测，例如：如果起跳后落地了，把方向从W改成D
protected:
    int x = windowsLenth/8;//中心的X坐标
    int y = 4 * windowsWidth / 5;
};
class Can :public Object
{
public:
    Can();
    void move();
    //每次move完都要draw
    void draw();
    void changeState();
    void jump();
    char direction; //W表示向上 S表示向下 A表示向左 D表示向右
private:
    int level;
    int v_y;//y方向上的速度
    const int vAfterJump = -15;
};
//class Coin :public Object
//{
//public:
//    Coin();
//    //定位一个拉环位置
//    void move();
//    void draw();
//private:
//    //Coin一定概率下随机出现 随机出现的一个就是一个对象
//    bool isEaten;
//};