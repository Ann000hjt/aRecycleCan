#include"Object.h"
#include"time.h"
#include<stdlib.h>
#define random(m,n) (rand()%(n-m+1)+m)
//随机数范围为m~n闭区间

const int gravity = 2;//模拟重力


Can::Can()
{
    level = LEVEL_0;
    v_y = 0;
    direction = 'D';
}
void Can::jump()
{
    direction = 'W';
    v_y = vAfterJump;
}
void Can::move()
{
    if (direction == 'W')
    {
        if (y + v_y <= 8 * windowsWidth1 / 15)
        {
            y = y + v_y;
        }
        else
        {
            y = 8 * windowsWidth1 / 15;
        }
        
        v_y = v_y + gravity;
    }
    if (y > 8 * windowsWidth1 / 15)
    {
        y = 8 * windowsWidth1 / 15;
    }
}
void Can::changeState()
{
    //如果方向为W，并且是在下落过程，并且落到地面了，则方向更改为D
    if (direction == 'W' && v_y > 0 && y >= 8 * windowsWidth1 / 15)
    {
        this->direction = 'D';
    }
}

int Can::getLength()
{
    return canLength;
}
int Can::getWidth()
{
    return canWidth;
}
void Can::plusScore()
{
    score++;
}
int Can::getScore()
{
    return score;
}
void Can::cutLife()
{
   // if(life==1)触发游戏结束
    life--;
}
void Can::plusLife()
{
    if(life>=1&&life<3)
        life++;
}
int Can::getLife()
{
    return life;
}
void Can::init()
{
    life = 3;
    level = LEVEL_0;
    v_y = 0;
    direction = 'D';
    x= windowsLenth1 / 8;
    y= 8 * windowsWidth1 /15;
}


Barrier::Barrier(int bmpLength, int bmpWidth)
{
    x = windowsLenth1;
    y = 2 * windowsWidth1 / 3;
    barrierLength = bmpLength;
    barrierWidth = bmpWidth;
}
void Barrier::move()
{
    x = x + v_x;
}
void Barrier::changeState()
{
    if (x <= -barrierLength||isCrush==true)
    {
        x = windowsLenth1 ;
        init();
    }
}
void Barrier::Crush()
{
    isCrush = true;
}
void Barrier::init()
{
    x = windowsLenth1;
    y = 2 * windowsWidth1 / 3;
    this->v_x = -random(15,20);
    isCrush = false;
}
int Barrier::getLength()
{
    return barrierLength;
}
int Barrier::getWidth()
{
    return barrierWidth;
}


Button::Button(int x, int y, int bmpLength, int bmpWidth)
{
    this->x = x;
    this->y = y;
    buttonLength = bmpLength;
    buttonWidth = bmpWidth;
}
int Button::getLength()
{
    return buttonLength;
}
int Button::getWidth()
{
    return buttonWidth;
}


Coin::Coin(int Cointype)
{
    this->type = Cointype;
    this->x = windowsLenth1;
    //减少两个道具重合的纪律
    if(type==1)
        this->y = random(windowsWidth1 / 5, 2 * windowsWidth1 / 5);
    else
        this->y = random(windowsWidth1 / 7, 2 * windowsWidth1 / 3);
    isEaten = false;
}
bool Coin::getEatenState()
{
    return isEaten;
}
void Coin::Eaten()
{
    //if碰撞，isEaten=true
    isEaten = true;
}
void Coin::changeState()
{
    if (x <= 0||isEaten==true)
    {
        this->init();
    }
}
void Coin::move()
{
    x = x + v_x;
    //y = y + v_y;
}
void Coin::init()
{
    //初始化拉环 随机每次出现的位置
    srand((unsigned)time(NULL));//设置随机数种子
    
    x = windowsLenth1;
    if (type == 1)
    {
        v_x = -8;
        this->y = random(windowsWidth1 / 5, 2 * windowsWidth1 / 5);
    }
    else
    {
        v_x = -5;
        this->y = random(windowsWidth1 / 7, 2*windowsWidth1 / 3);
    }
   
    //y = random(windowsWidth1 / 7, windowsWidth1/3);
    isEaten = false;
}
int Coin::getType() 
{
    return type;
}


Title::Title(int x, int y, int bmpLength, int bmpWidth)
{
    this->x = x;
    this->y = y;
    titleLength = bmpLength;
    titleWidth = bmpWidth;
}

Background::Background(int x, int y, int bmpLength, int bmpWidth)
{
    this->x = x;
    this->y = y;
    backgroundLength = bmpLength;
    backgroundWidth = bmpWidth;
}
