#include<Windows.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>

#include"Object.h"
#include"drawAll.h"
#include"upDateData.h"
#include"positonTest.h"

using namespace std;

const int BEFORE_START = 0;
const int BEFORE_INIT = 1;
const int PLAYING_GAME = 2;
const int ACHIEVEMENT_SHOW = 3;

const int gravity = 2;//模拟重力

const int TICKS_PER_SECOND = 50;//50帧每秒的更新速度
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;//1000帧所需的时间？
const int MAX_FRAMESKIP = 5;//帧数可以缩小到最低的倍数

int windowsLenth = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
int windowsWidth = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */

//创建主角易拉罐
Can hh;
//创建按钮
Button newGame(windowsLenth / 2, 3 * windowsWidth / 8, 320, 180);
Button continueGame(windowsLenth / 2, 5 * windowsWidth / 8, 320, 180);
Button achievement(windowsLenth / 2, 7 * windowsWidth / 8, 320, 180);
Button back(windowsLenth/2, 200, 160, 90);//想放在右上角，每个屏幕不同，改的时候改这里就ok  我先换别的位置检测
//游戏背景不是按钮，但是由于没写相应的类，目前使用按钮
Background backgroundPlayingGame(0, 0, windowsLenth, windowsWidth);
//生命值属于title
Title lifeOfcan(50, 50, 90, 160);
Title achievement_t(windowsLenth / 2, 50, 160, 90);
//创建障碍物
Barrier unrecyclable;
//创建拉环
Coin coin1;

static int flag = BEFORE_START;//设置游戏状态为：进入游戏前
//?

bool isFirst = true;


SMALL_RECT SizeOfWindow(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &info);
    return info.srWindow;
}
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);//回调函数
int main()
{         
    //定义窗口缓冲区信息结构体  
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    //加载图片资源，建议另加一个resource.cpp文件专门加载各种图片资源
    //主角
    HBITMAP can180320 = (HBITMAP)LoadImage(NULL, "can180320.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP jumpcan180320 = (HBITMAP)LoadImage(NULL, "jumpcan180320.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //按钮
    HBITMAP continue320180 = (HBITMAP)LoadImage(NULL, "continue320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP newGame320180 = (HBITMAP)LoadImage(NULL, "newGame320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP achievement320180 = (HBITMAP)LoadImage(NULL, "achievement320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP back16090 = (HBITMAP)LoadImage(NULL, "back16090.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //背景、标题
    HBITMAP background= (HBITMAP)LoadImage(NULL, "background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP achievement16090 = (HBITMAP)LoadImage(NULL, "achievement16090.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //其他
    HBITMAP unrecyclable200200 = (HBITMAP)LoadImage(NULL, "unrecyclable200200.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP coin12080= (HBITMAP)LoadImage(NULL, "coin12080.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP life4580 = (HBITMAP)LoadImage(NULL, "life4580.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


    //获得标准输出设备句柄
    HANDLE	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //获得标准输入设备句柄
    HANDLE	hIn = GetStdHandle(STD_INPUT_HANDLE);
    //定义输入事件结构体  
    INPUT_RECORD inputRecord;
    //定义光标结构体
    CONSOLE_CURSOR_INFO CursorInfo;
   
    DWORD mode;
    GetConsoleMode(hIn, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;  //移除快速编辑模式
    mode &= ~ENABLE_INSERT_MODE;      //移除插入模式
    //mode &= ~ENABLE_MOUSE_INPUT;//？不知道什么模式
    SetConsoleMode(hIn, mode);
    //得到前台窗口（用户当前工作的窗口）句柄
    HWND hwnd = GetForegroundWindow();
    /* 获取窗口信息 */
    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);

    //锁定窗口全屏
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_THICKFRAME);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, windowsLenth, windowsWidth, 0);
     
   
    // 改为固定窗口大小
    RECT rc;
    GetWindowRect(hwnd, &rc); //获得cmd窗口对应矩形

    //改变cmd窗口风格
    SetWindowLongPtr(hwnd,GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
    //因为风格涉及到边框改变，必须调用SetWindowPos，否则无效果
    SetWindowPos(hwnd,NULL, rc.left,rc.top,rc.right - rc.left, rc.bottom - rc.top, NULL);

    //取消滚动条（不知道具体是哪一句）->（point那句不可以删）
    GetConsoleScreenBufferInfo(hOut, &csbi);
    SMALL_RECT rect = SizeOfWindow(hOut);
   //定义缓冲区大小 
    COORD size = { rect.Right + 1,rect.Bottom + 1 };
    SetConsoleScreenBufferSize(hOut, size);//point

    // 隐藏控制台光标
    GetConsoleCursorInfo(hOut, &CursorInfo);//获取控制台光标信息
    CursorInfo.bVisible = false; //隐藏控制台光标
    SetConsoleCursorInfo(hOut, &CursorInfo);//设置控制台光标状态

    DWORD res;       //用于存储读取记录
    COORD pos;       //用于存储鼠标当前位置  
    
    DWORD next_game_tick=(DWORD)0;
    int loops;
    float interpolation;//计算等价的帧数//渲染帧数是预测与插值实现的

    HWND cmd = GetConsoleWindow();//控制台窗口句柄
    //得到设备场景（设备描述表）句柄：窗口DC
    HDC hDC = GetDC(cmd);//屏幕显示DC
    //依据屏幕显示DC创建内存DC设备描述表句柄
    HDC dcMEM = CreateCompatibleDC(hDC);//内存兼容DC
    MSG msg;
    int timerID = 1;//TimerID
    int period = 40;//40ms调用一次timer
    //UINT_PTR MyID1 = SetTimer(NULL, timerID, period, (TIMERPROC)&TimerProc);
    DWORD InNum = 0;//用来保存缓冲区输入事件的数量
    DWORD judge = 1;//用来与InNum比较大小
    //转化类型，稍后把InputNum传递给GetNumberOfConsoleInputEvents
    LPDWORD InputNum = &InNum;

    POINT p;//鼠标坐标

    //初始化inputRecord
    ReadConsoleInput(hIn, &inputRecord, 1, &res);       //读取输入事件
    for (;;)
    {   
        //当有输入事件的时候才调用ReadConsoleInput
        //防止函数停下来等待输入消息，造成主循环阻塞
        GetNumberOfConsoleInputEvents(hIn, InputNum);
        if (*InputNum >= judge)
        {
            ReadConsoleInput(hIn, &inputRecord, 1, &res);       //读取输入事件
        }
        pos = inputRecord.Event.MouseEvent.dwMousePosition;     //获得当前鼠标位置  
        GetCursorPos(&p);
        if (inputRecord.EventType == MOUSE_EVENT)     //如果当前为鼠标事件  
        {
            if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//左键点击
            {
                switch (flag)
                {
                case BEFORE_START://这个界面的按钮有：开始，继续，成就，退出，设置（？）
                {
                    //SetConsoleCursorPosition(hOut, pos);//把光标移动到pos位置
                    if(isKickButton(p.x,p.y,newGame,8))
                    {
                        isFirst = true;
                        //KillTimer(NULL, MyID1);
                        flag = BEFORE_INIT;
                    }
                    else if (isKickButton(p.x, p.y, continueGame, 8))
                    {
                        isFirst = true;
                        flag = PLAYING_GAME;
                    }
                    else if (isKickButton(p.x, p.y, achievement, 8))
                    {
                        isFirst = true;
                        flag = ACHIEVEMENT_SHOW;
                    }
                    break;
                }
                case PLAYING_GAME:
                    if (isKickButton(p.x, p.y, back, 8))
                    {
                        flag = BEFORE_START;
                    }
                    break;
                case ACHIEVEMENT_SHOW:
                    if (isKickButton(p.x, p.y, back, 8))
                    {
                        flag = BEFORE_START;
                    }
                    break;
                default:
                    break;
                }
            }
        }
        //如果当前事件是键盘事件
        else if (inputRecord.EventType == KEY_EVENT)
        {
            switch (flag)
            {
            case PLAYING_GAME:
            {
                if (inputRecord.Event.KeyEvent.wVirtualKeyCode == 0x57 && inputRecord.Event.KeyEvent.bKeyDown && hh.direction != 'W')
                {

                    //用户按下了W
                    hh.jump();
                    inputRecord.Event.KeyEvent.wVirtualKeyCode = '0';//为了知道此时没有按W，我把他设置成现在在按0

                }
                break;
            }
            }
        }

        DrawBmp(hDC, dcMEM, background, backgroundPlayingGame, windowsLenth, windowsWidth, isFirst);
        isFirst = false;
        switch (flag)
        {
        case BEFORE_START:
        {
            //BEFOR_START是游戏初始界面
            DrawBmp(hDC, dcMEM, newGame320180, newGame, 320, 180, isFirst);//画到内存dc上
            DrawBmp(hDC, dcMEM, continue320180, continueGame, 320, 180, isFirst);//画到内存dc上
            DrawBmp(hDC, dcMEM, achievement320180, achievement, 320, 180, isFirst);//画到内存dc上
            break; 
        }
        case BEFORE_INIT:
        {
            next_game_tick = (DWORD)GetTickCount64();//返回从程序开始运行到现在的时间/ms
            //初始化易拉罐位置、属性
            hh.setX(windowsLenth / 8);
            hh.setY(3*windowsWidth / 5);
            hh.init();

            //初始化拉环位置、属性
            coin1.init();
            
            flag = PLAYING_GAME;
            break;
        }
        case PLAYING_GAME:
        {
            //system("cls");
            //update，更新数据，后面会学习游戏主循环，控制更新数据和渲染的频率，目前还没做

            //玩家输入不需要以那么高的帧率更新，前面设置为每秒50帧
            loops = 0;
            while (GetTickCount64() > next_game_tick && loops < MAX_FRAMESKIP)
            {
                //hh的操作属于upDate_Data 每秒不多不少地被调用50次
                upDate_data(hh);
                //此处需要有障碍物，拉环等的update（更新函数）
                unrecyclable.move();
                coin1.move();
                if (isCoinEaten(hh, coin1) == true)
                {
                    coin1.changeState();
                }
                next_game_tick += SKIP_TICKS;
                loops++;
            }
            interpolation = float(GetTickCount64() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);
            
            //画返回键
            DrawBmp(hDC, dcMEM, back16090, back, 160, 90, isFirst);

            //画生命值
            switch (hh.getLife())
            {
            case 3:
                lifeOfcan.setX(190);
                DrawBmp(hDC, dcMEM, life4580, lifeOfcan, 90, 180, isFirst);
            case 2:
                lifeOfcan.setX(120);
                DrawBmp(hDC, dcMEM, life4580, lifeOfcan, 90, 180, isFirst);
            case 1:
                lifeOfcan.setX(50);
                DrawBmp(hDC, dcMEM, life4580, lifeOfcan, 90, 180, isFirst);
                break;
            default:
                break;
            }
            //上面那个方法更快，下面是蠢蠢法（可删去）
            /*if (hh.getLife() >= 1)
            {
                lifeOfcan.setX(50);
                DrawBmp(hDC, dcMEM, life4580, lifeOfcan, 90, 180, isFirst);
                if (hh.getLife() >= 2)
                {
                    lifeOfcan.setX(120);
                    DrawBmp(hDC, dcMEM, life4580, lifeOfcan, 90, 180, isFirst);
                    if (hh.getLife() == 3)
                    {
                        lifeOfcan.setX(190);
                        DrawBmp(hDC, dcMEM, life4580, lifeOfcan, 90, 180, isFirst);
                    }
                }
            }*/
                
            //画罐子
            if(hh.direction=='W')
                DrawBmp(hDC, dcMEM, jumpcan180320, hh, 180, 320, isFirst, interpolation);
            else
                DrawBmp(hDC, dcMEM, can180320, hh, 180, 320, isFirst, interpolation);
            
            //此处除了罐子外，其他的（障碍物，拉环）也都需要差值预测
            DrawBmp(hDC, dcMEM, unrecyclable200200, unrecyclable, 200, 200, isFirst);
            if (coin1.getEatenState()==false)
                DrawBmp(hDC, dcMEM, coin12080, coin1, 120, 80, isFirst);

            isFirst = false;//此处修改为isFirst防止误清游戏画面
            break;
        }
        case ACHIEVEMENT_SHOW:
            DrawBmp(hDC, dcMEM, achievement16090, achievement_t, 160, 90, isFirst);
            //画返回按钮，不然卡在成就界面了
            DrawBmp(hDC, dcMEM, back16090, back, 160, 90, isFirst);

            break;
        }

        //具体作用不了解，把getmessage换成peekmessage防止阻塞主循环
        PeekMessage(&msg, NULL, 0, 0,PM_NOREMOVE);
        if (msg.message == WM_TIMER)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        //把内存dc上的东西一次性画到显示dc上
        BitBlt(hDC, 0, 0, windowsLenth, windowsWidth, dcMEM, 0, 0, SRCCOPY); //此处第一个参数才为hDC,即窗口句柄

    }
    DeleteDC(dcMEM);
    CloseHandle(hOut);
    CloseHandle(hIn);
    DestroyWindow(hwnd);
    DeleteDC(hDC);
    
    DestroyWindow(cmd);
    return 0;

}
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{

    if (flag == BEFORE_START)
    {
    }
    else
    {

    }
}