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
    //每次move完都要draw
    void draw();
private:
    int level;
    int v_x;//x方向上的速度
    int v_y;//y方向上的速度
    char direction;
    //W表示向上 S表示向下 A表示向左 D表示向右
    int score;//得分
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