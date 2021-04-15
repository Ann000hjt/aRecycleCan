#include"Object.h"

Can::Can()
{
    level = LEVEL_0;
    v_y = 0;
    direction = 'D';
    score = 0;
}
void Can::move()
{
    //move将在一个循环函数里面
    char c = _getch();
    switch (c)
    {
    case 13://回车键
        cout << "wait..." << endl;
        system("pause");
        //暂用这个 功能是暂停游戏 flag=
        break;
    case 80://向下
        direction = 'S';
        break;
    case 72://向上
        if (direction != 'W')v_y = 1;//速度先假设是1，如果方向已经是向上就是无效操作
        direction = 'W';
        break;
    case 75://向左
        direction = 'A';
        v_x = -1;//计算位移的时候利用物理公式
        this->x--;
        break;
    case 77://向右
        direction = 'D';
        v_x = 1;
        this->x += 1;//通过设置这里每一次加的值来实现速度的快慢
        break;
    default:
        break;
    }
}
void Can::draw()
{
    //can是一个位图
    HMODULE hKernel32 = GetModuleHandle("kernel32");
    HWND cmd = GetConsoleWindow();//控制台窗口句柄

    HDC dc = GetDC(cmd);
    HBITMAP hBitmap;
    HDC cmdmem = CreateCompatibleDC(dc);
    //if (this->direction == 'A')
    //{
    //    hBitmap = (HBITMAP)LoadImage(NULL, "left.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //}
    //else
    //{
    //    hBitmap = (HBITMAP)LoadImage(NULL, "right.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //}
    hBitmap = (HBITMAP)LoadImage(NULL, "continue320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    SelectObject(cmdmem, hBitmap);

    int buttonStartWidth = 1900;
    int buttonStartHeight = 900;

    BitBlt(dc, this->x, this->y, buttonStartWidth, buttonStartHeight, cmdmem, 0, 0, SRCCOPY);
}