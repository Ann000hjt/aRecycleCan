#include<Windows.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>

#include"Object.h"
#include"drawAll.h"
#include"upDateData.h"
#include"positonTest.h"


#define qdo 262 
#define qre 294
#define qmi 330
#define qfa 349
#define qso 392
#define qla 440
#define qsi 494
#define do 523
#define re 578
#define mi 659
#define fa 698
#define so 784
#define la 880
#define si 988
#define do1 1046
#define re1 1175
#define mi1 1318
#define fa1 1480
#define so1 1568
#define la1 1760
//半拍200ms
#define half 200

using namespace std;

const int BEFORE_START = 0;
const int BEFORE_INIT = 1;
const int PLAYING_GAME = 2;
const int ACHIEVEMENT_SHOW = 3;
const int GAME_OVER = 4;

const int gravity = 2;//模拟重力

const int TICKS_PER_SECOND = 50;//50帧每秒的更新速度
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;//1000帧所需的时间？
const int MAX_FRAMESKIP = 5;//帧数可以缩小到最低的倍数

int windowsLenth1 = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 1280像素 */
int windowsWidth1 = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 720像素 */

int windowsLenth = 855;//实际画出来的宽度 855像素 
int windowsWidth = 480;//实际画出来的高度 480像素
                       
//这里其实不太好，因为每台电脑的压缩比值有差异，但暂时先这样实现
//校正系数->画bmp整体有横向和纵向的缩小比值
double correctX = (double)windowsLenth / windowsLenth1;
double correctY = (double)windowsWidth / windowsWidth1;




//创建主角易拉罐
Can hh;
//创建按钮
Button newGame((windowsLenth1-240)/2, 4*windowsWidth1/15, 240, 125);
Button continueGame((windowsLenth1 - 240) / 2, 7 * windowsWidth1 / 15, 240, 125);
Button achievement((windowsLenth1 - 240)/2, 10 * windowsWidth1 / 15, 240, 125);
Button back(windowsLenth1-100, 0, 100, 60);
//游戏背景不是按钮，但是由于没写相应的类，目前使用按钮
Background backgroundPlayingGame(0, 0, 1280, 720);
Background backgroundInit(0, 0, 1280, 720);
Background backgroundOver(0, 0, 1280, 720);
//创建标题（不能按的一类东西）
Title lifeOfcan(50, 50, 90, 160);
Title achievement_t((windowsLenth1 - 240) / 2, windowsWidth1 / 15, 160, 90);
Title coin_t(2*windowsLenth1/ 3,  windowsWidth1 / 15, 60, 40);
//创建障碍物
Barrier unrecyclable;
//创建拉环道具
Coin coin1(1);
//创建加生命值道具
Coin coin2(2);


static int flag = BEFORE_START;//设置游戏状态为：进入游戏前
//?

bool isFirst = true;
bool jumpFlagDown = false;
bool jumpFlagEver = false;
SMALL_RECT SizeOfWindow(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &info);
    return info.srWindow;
}
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);//回调函数

DWORD WINAPI Thread1(LPVOID);
int main()
{         
    //加载图片资源，建议另加一个resource.cpp文件专门加载各种图片资源
    //主角
    HBITMAP can150250 = (HBITMAP)LoadImage(NULL, "can150250.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP jumpcan150250 = (HBITMAP)LoadImage(NULL, "jumpcan150250.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP overcan180320 = (HBITMAP)LoadImage(NULL, "overcan180320.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //按钮
    HBITMAP continue240125 = (HBITMAP)LoadImage(NULL, "continue240125.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP newGame240125 = (HBITMAP)LoadImage(NULL, "newGame240125.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP achievement240125 = (HBITMAP)LoadImage(NULL, "achievement240125.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP back10060 = (HBITMAP)LoadImage(NULL, "back10060.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //背景、标题
    HBITMAP background= (HBITMAP)LoadImage(NULL, "background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP initBackground = (HBITMAP)LoadImage(NULL, "initBackground1280720.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP overBackground = (HBITMAP)LoadImage(NULL, "overBackground1280720.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP achievement16090 = (HBITMAP)LoadImage(NULL, "achievement16090.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP coin6040 = (HBITMAP)LoadImage(NULL, "coin6040.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //其他
    HBITMAP unrecyclable130130 = (HBITMAP)LoadImage(NULL, "unrecyclable130130.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP coin12080= (HBITMAP)LoadImage(NULL, "coin12080.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP life4580 = (HBITMAP)LoadImage(NULL, "life4580.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP plusLife100100 = (HBITMAP)LoadImage(NULL, "plusLife100100.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


    //定义窗口缓冲区信息结构体  
    CONSOLE_SCREEN_BUFFER_INFO csbi;
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
    SetWindowPos(hwnd, HWND_TOP, 0, 0, windowsLenth1, windowsWidth1, 0);

    //改变宽高（顺序不能与下面调换，这个不能用，用了之后程序跑不动）
    //system("mode con cols=100 lines=30");

    //改为固定窗口大小->不改了
    //RECT rc;
    //获得cmd窗口对应矩形
    //GetWindowRect(hwnd, &rc); 
    //改变cmd窗口风格
    //SetWindowLongPtr(hwnd,GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
    //因为风格涉及到边框改变，必须调用SetWindowPos，否则无效果

    //锁定窗口全屏
    //SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_THICKFRAME);
    //SetWindowPos(hwnd,NULL, rc.left,rc.top,rc.right - rc.left, rc.bottom - rc.top, NULL);
   
    ////固定窗口大小
    //MoveWindow(hwnd, rc.left, rc.top, 800, 515, TRUE); // 815 width, 515 height

    //取消滚动条（不知道具体是哪一句）->（point那句不可以删）
    SMALL_RECT rect = SizeOfWindow(hOut);
    COORD size = { rect.Right + 1,rect.Bottom + 1 };
    //设置缓冲区大小
    SetConsoleScreenBufferSize(hOut, size);//point
    GetConsoleScreenBufferInfo(hOut, &csbi);//用于检索指定的控制台屏幕缓冲区的信息
    //重置窗口位置和大小
    //SetConsoleWindowInfo(hOut, true, &rect);
    

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


    HANDLE hThread;
    DWORD threadID;
    hThread = CreateThread(NULL, 0, Thread1, 0, 0, &threadID);//创建进程






    //初始化inputRecord
    ReadConsoleInput(hIn, &inputRecord, 1, &res);       //读取输入事件
    for (;;)
    {   
        //cout << "x:" << windowsLenth1 << "  y:" << windowsWidth1<<" ";

        //当有输入事件的时候才调用ReadConsoleInput
        //防止函数停下来等待输入消息，造成主循环阻塞
        GetNumberOfConsoleInputEvents(hIn, InputNum);
        if (*InputNum >= judge)
        {
            ReadConsoleInput(hIn, &inputRecord, 1, &res);       //读取输入事件
        }
        pos = inputRecord.Event.MouseEvent.dwMousePosition;     //获得当前鼠标位置  
        GetCursorPos(&p);
        ScreenToClient(hwnd, &p);    // 将鼠标指针位置转换为窗口坐标
        if (inputRecord.EventType == MOUSE_EVENT)     //如果当前为鼠标事件  
        {
            if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//左键点击
            {
                switch (flag)
                {
                case BEFORE_START://这个界面的按钮有：开始，继续，成就，退出，设置（？）
                {

                   /* cout << " x:" << p.x << " y:" << p.y << endl;
                    cout << correctX*newGame.getX() << " " << correctY*newGame.getY() << endl;
                    cout << newGame.getLength() << endl;*/

                    //SetConsoleCursorPosition(hOut, pos);//把光标移动到pos位置
                    if(isKickButton(p.x,p.y,newGame,0))
                    {
                        //KillTimer(NULL, MyID1);
                        isFirst = true;
                        flag = BEFORE_INIT;
                    }
                    else if (isKickButton(p.x, p.y, continueGame, 0))
                    {
                        isFirst = true;
                        if (hh.getv_y() != 0)
                            flag = PLAYING_GAME;
                        else
                            flag = BEFORE_INIT;
                    }
                    else if (isKickButton(p.x, p.y, achievement, 0))
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
                case GAME_OVER:
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
        if (inputRecord.EventType == KEY_EVENT)
        {
            switch (flag)
            {
            case PLAYING_GAME:
            {
                if (inputRecord.Event.KeyEvent.wVirtualKeyCode == 0x57 && inputRecord.Event.KeyEvent.bKeyDown )
                {
                    //用户按下了W
                    jumpFlagDown = true;
                    //inputRecord.Event.KeyEvent.wVirtualKeyCode = '0';//为了知道此时没有按W，我把他设置成现在在按0
                }
                else
                {
                    jumpFlagDown = false;
                }
                break;
            }
            }
        }
        DrawBmp(hDC, dcMEM, background, backgroundPlayingGame, 1280, 720, isFirst);
        isFirst = false;
        switch (flag)
        {
        case BEFORE_START:
        {
            DrawBmp(hDC, dcMEM, initBackground, backgroundInit, 1280,720, true);
            //BEFOR_START是游戏初始界面
            DrawBmp(hDC, dcMEM, newGame240125, newGame, 240, 125, isFirst);//画到内存dc上
            DrawBmp(hDC, dcMEM, continue240125, continueGame, 240, 125, isFirst);//画到内存dc上
            DrawBmp(hDC, dcMEM, achievement240125, achievement, 240, 125, isFirst);//画到内存dc上
            break; 
        }
        case BEFORE_INIT:
        {
            next_game_tick = (DWORD)GetTickCount64();//返回从程序开始运行到现在的时间/ms
            //初始化易拉罐位置、属性
            hh.init();

            //初始化拉环位置、属性
            coin1.init();
            coin2.init();

            //初始化障碍物位置、属性
            unrecyclable.init();
            
            flag = PLAYING_GAME;
            break;
        }
        case PLAYING_GAME:
        {
            //system("cls");
            //update，更新数据，后面会学习游戏主循环，控制更新数据和渲染的频率，目前还没做
            if(jumpFlagDown)
            {
                jumpFlagEver = true;
            }
            
            //玩家输入不需要以那么高的帧率更新，前面设置为每秒50帧
            loops = 0;
            while (GetTickCount64() > next_game_tick && loops < MAX_FRAMESKIP)
            {
                //hh的操作属于upDate_Data 每秒不多不少地被调用50次
                upDate_data(hh);
                upDate_data(unrecyclable);
                upDate_data(coin1);
                upDate_data(coin2);

                if (isCoinEaten(hh, coin1) == true)
                {
                    coin1.Eaten();
                    hh.plusScore();
                }
                if (isCoinEaten(hh, coin2) == true)
                {
                    coin2.Eaten();
                    hh.plusLife();
                }
                if (isBarrierCrush(hh, unrecyclable) == true)
                {
                    unrecyclable.Crush();
                    hh.cutLife();
                }

                //防止can往下弹
                if (jumpFlagEver && !jumpFlagDown && hh.direction != 'W')
                {
                    hh.jump();
                    jumpFlagEver = false;
                }

                next_game_tick += SKIP_TICKS;
                loops++;
            }
            interpolation = float(GetTickCount64() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);
            
            //画返回键
            DrawBmp(hDC, dcMEM, back10060, back, 100, 60, isFirst);

            //画生命值
            switch (hh.getLife())
            {
            case 3:
                lifeOfcan.setX(6 * windowsLenth1 / 15);
                DrawBmp(hDC, dcMEM, life4580, lifeOfcan, 45, 80, isFirst);
            case 2:
                lifeOfcan.setX(7 * windowsLenth1 / 15);
                DrawBmp(hDC, dcMEM, life4580, lifeOfcan, 45, 80, isFirst);
            case 1:
                lifeOfcan.setX(8 * windowsLenth1 / 15);
                DrawBmp(hDC, dcMEM, life4580, lifeOfcan, 45, 80, isFirst);
                break;
            default:
                break;
            }

            //画拉环值
            DrawBmp(hDC, dcMEM, coin6040, coin_t, 60, 40, isFirst);
            //指定位置输出数字，移动到某个位置输出的函数我不记得了
            
                
            //画罐子（跳起来和站着的两个状态）
            if(hh.direction=='W')
                DrawBmp(hDC, dcMEM, jumpcan150250, hh, 150, 250, isFirst, interpolation);
            else
                DrawBmp(hDC, dcMEM, can150250, hh, 150, 250, isFirst, interpolation);
            
            //此处除了罐子外，其他的（障碍物，拉环）也都需要差值预测
            DrawBmp(hDC, dcMEM, unrecyclable130130, unrecyclable, 200, 200, isFirst);
            if (coin1.getEatenState()==false)
                DrawBmp(hDC, dcMEM, coin12080, coin1, 120, 80, isFirst);
            if (coin2.getEatenState() == false)
                DrawBmp(hDC, dcMEM, plusLife100100, coin2, 100, 100, isFirst);

            isFirst = false;//此处isFirst赋值为false防止误清游戏画面
            
            if (hh.getLife() <= 0)
                flag = GAME_OVER;
            break;
        }
        case ACHIEVEMENT_SHOW:
            DrawBmp(hDC, dcMEM, achievement16090, achievement_t, 160, 90, isFirst);
            //画返回按钮，不然卡在成就界面了
            DrawBmp(hDC, dcMEM, back10060, back, 100, 60, isFirst);
            break;
        case GAME_OVER:
            //GAME_OVER是游戏结束界面
            DrawBmp(hDC, dcMEM, overBackground, backgroundOver, 1280, 720, true);
            isFirst = false;
            hh.setX(windowsLenth / 2);
            hh.setY(2*windowsWidth1 / 5);
            //背景上的主角和返回键
            DrawBmp(hDC, dcMEM, overcan180320, hh, 180, 320, isFirst);
            DrawBmp(hDC, dcMEM, back10060, back, 100, 60, isFirst);
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
        BitBlt(hDC, 0, 0, windowsLenth1, windowsWidth1, dcMEM, 0, 0, SRCCOPY); //此处第一个参数才为hDC,即窗口句柄

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
DWORD WINAPI Thread1(LPVOID)//进程函数，用来播放背景音乐
{
    int tiger2[][2] =
    {
        {do,2},{re,2},{mi,2},{do,2},//两只老虎
        {re,2},{so,2},{so,2},{0,2},//爱跳舞
        {mi,2},{la,1},{la,1},{la,2},{la,2},//小兔子乖乖
        {so,1},{mi,1},{so,2},{mi,2},{0,2},//拔萝卜
        {do,3},{do,1},{do,2},{la,1},{la,1},//我和小鸭子
        {so,2},{mi,2},{so,2},{0,2},//学走路
        {re,1},{re,2},{mi,1},{mi,1},{re,1},{do,1},{mi,1},//童年是最美的礼
        {re,4},{qso,1},{qla,1},{qsi,1},{re,1},//物
        {do,2},{re,2},{mi,2},{do,2},//小螺号呀
        {re,2},{so,1},{so,1},{so,2},{0,2},//滴滴地吹
        {mi,2},{la,2},{la,2},{do1,2},//我学海鸥
        {si,2},{la,2},{so,2},{0,2},//展翅飞
        {do,3},{do,1},{do,2},{la,2},//不怕风雨
        {so,2},{so,2},{mi,2},{0,2},//不怕累
        {re,1},{re,2},{mi,1},{mi,1},{re,1},{do,1},{re,1},//快快把本领都学
        {do,4},{do,1},{re,1},{mi,1},{so,1},//会,宝
        {do1,3},{do1,1},{do1,1},{so,1},{mi,1},{do1,1},//贝，星星为你指
        {si,4},{0,2},{0,1},{mi,1},//路，宝
        {la,3},{la,1},{la,1},{so,1},{la,1},{si,1},//贝，月亮为你祝
        {so,4},{0,2},{0,2},//福
        {mi,2},{so,1},{so,1}, {so,2},{do1,2},//成长是快乐
        {re1,3},{re1,1},{la,4},//的旅途
        {so,1},{so,1},{so,1}, {la,1},{si,1}, {la,1},{si,1}, {do1,1},//勇敢迈开你的脚
        {re1,6},{0,1},{so,1},//步，宝
        {do1,3},{do1,1},{do1,1},{so,1},{mi,1},{do1,1},//贝，妈妈怀里安
        {si,4},{0,2},{0,1},{mi,1},//睡，宝
        {la,3},{la,1},{la,1},{so,1},{la,1},{si,1},//爸爸是你椅
        {so,4},{0,2},{0,2},//背
        {mi,2},{so,2},{so,2},{do1,1},{do1,1},//你是我们的
        {re1,1},{re1,1},{re1,2},{la,4},//心肝宝贝
        {so,1},{so,1},{so,1},{la,1},{si,1},{do1,1},{do1,1},{re1,1},//爸爸妈妈的爱永相
        {do1,8},//随
        {0,8}
    };
    while (1)
    {
        int i = 0;
        for (; i < sizeof(tiger2) / sizeof(int) / 2; i++)
        {
            if (tiger2[i][0] == 0)
            {
                Sleep(tiger2[i][1] * half);
            }
            else
            {
                Beep(tiger2[i][0], tiger2[i][1] * half);
            }
        }
    }
}