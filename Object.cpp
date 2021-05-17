#include"Object.h"
const int gravity = 3;//模拟重力
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
        y = y + v_y;
        v_y = v_y + gravity;
    }
    if (y > 3 * windowsWidth / 5)
    {
        y = 3 * windowsWidth / 5;
    }
}
void Can::draw()
{
    
}

void Can::changeState()
{
    //如果方向为W，并且是在下落过程，并且落到地面了，则方向更改为D
    if (direction == 'W' && v_y > 0 && y == 3 * windowsWidth / 5)
    {
        this->direction = 'D';
    }
}
Barrier::Barrier()
{
    x = 6 * windowsLenth / 8;
    y = 3 * windowsWidth / 5;
}
void Barrier::move()
{
    x = x + v_x;
}
void Barrier::draw()
{

}
void Barrier::changeState()
{
    if (x <= 0)
    {
        x = 6 * windowsLenth / 8;
    }
}

Button::Button(int x, int y, int bmpLength, int bmpWidth)
{
    this->x = x;
    this->y = y;
    buttonLength = bmpLength;
    buttonWidth = bmpWidth;
}
void Button::changeState()
{

}
void Button::move()
{

}
void Button::draw()
{

}

int Button::getLength()
{
    return buttonLength;
}
int Button::getWidth()
{
    return buttonWidth;
}


Coin::Coin()
{
    //之后要用随机数创建
    this->x = 3 * windowsLenth / 5;
    this->y = 0;
}
void Coin::changeState()
{
    //if碰撞，isEaten=true
}
void Coin::move()
{
    x = x + v_x;
    y = y + v_y;
}
void Coin::draw()
{

}
