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

const int gravity = 2;//ģ������

const int TICKS_PER_SECOND = 50;//50֡ÿ��ĸ����ٶ�
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;//1000֡�����ʱ�䣿
const int MAX_FRAMESKIP = 5;//֡��������С����͵ı���

int windowsLenth = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
int windowsWidth = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */

//��������������
Can hh;
//������ť
Button newGame(windowsLenth / 2, 3 * windowsWidth / 8, 320, 180);
Button continueGame(windowsLenth / 2, 5 * windowsWidth / 8, 320, 180);
Button achievement(windowsLenth / 2, 7 * windowsWidth / 8, 320, 180);
Button back(windowsLenth/2, 200, 160, 90);//��������Ͻǣ�ÿ����Ļ��ͬ���ĵ�ʱ��������ok  ���Ȼ����λ�ü��
//��Ϸ�������ǰ�ť����������ûд��Ӧ���࣬Ŀǰʹ�ð�ť
Background backgroundPlayingGame(0, 0, windowsLenth, windowsWidth);
//����ֵ����title
Title lifeOfcan(50, 50, 90, 160);
Title achievement_t(windowsLenth / 2, 50, 160, 90);
//�����ϰ���
Barrier unrecyclable;
//��������
Coin coin1;

static int flag = BEFORE_START;//������Ϸ״̬Ϊ��������Ϸǰ
//?

bool isFirst = true;


SMALL_RECT SizeOfWindow(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &info);
    return info.srWindow;
}
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);//�ص�����
int main()
{         
    //���崰�ڻ�������Ϣ�ṹ��  
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    //����ͼƬ��Դ���������һ��resource.cpp�ļ�ר�ż��ظ���ͼƬ��Դ
    //����
    HBITMAP can180320 = (HBITMAP)LoadImage(NULL, "can180320.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP jumpcan180320 = (HBITMAP)LoadImage(NULL, "jumpcan180320.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //��ť
    HBITMAP continue320180 = (HBITMAP)LoadImage(NULL, "continue320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP newGame320180 = (HBITMAP)LoadImage(NULL, "newGame320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP achievement320180 = (HBITMAP)LoadImage(NULL, "achievement320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP back16090 = (HBITMAP)LoadImage(NULL, "back16090.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //����������
    HBITMAP background= (HBITMAP)LoadImage(NULL, "background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP achievement16090 = (HBITMAP)LoadImage(NULL, "achievement16090.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //����
    HBITMAP unrecyclable200200 = (HBITMAP)LoadImage(NULL, "unrecyclable200200.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP coin12080= (HBITMAP)LoadImage(NULL, "coin12080.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP life4580 = (HBITMAP)LoadImage(NULL, "life4580.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


    //��ñ�׼����豸���
    HANDLE	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //��ñ�׼�����豸���
    HANDLE	hIn = GetStdHandle(STD_INPUT_HANDLE);
    //���������¼��ṹ��  
    INPUT_RECORD inputRecord;
    //������ṹ��
    CONSOLE_CURSOR_INFO CursorInfo;
   
    DWORD mode;
    GetConsoleMode(hIn, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;  //�Ƴ����ٱ༭ģʽ
    mode &= ~ENABLE_INSERT_MODE;      //�Ƴ�����ģʽ
    //mode &= ~ENABLE_MOUSE_INPUT;//����֪��ʲôģʽ
    SetConsoleMode(hIn, mode);
    //�õ�ǰ̨���ڣ��û���ǰ�����Ĵ��ڣ����
    HWND hwnd = GetForegroundWindow();
    /* ��ȡ������Ϣ */
    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);

    //��������ȫ��
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_THICKFRAME);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, windowsLenth, windowsWidth, 0);
     
   
    // ��Ϊ�̶����ڴ�С
    RECT rc;
    GetWindowRect(hwnd, &rc); //���cmd���ڶ�Ӧ����

    //�ı�cmd���ڷ��
    SetWindowLongPtr(hwnd,GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
    //��Ϊ����漰���߿�ı䣬�������SetWindowPos��������Ч��
    SetWindowPos(hwnd,NULL, rc.left,rc.top,rc.right - rc.left, rc.bottom - rc.top, NULL);

    //ȡ������������֪����������һ�䣩->��point�Ǿ䲻����ɾ��
    GetConsoleScreenBufferInfo(hOut, &csbi);
    SMALL_RECT rect = SizeOfWindow(hOut);
   //���建������С 
    COORD size = { rect.Right + 1,rect.Bottom + 1 };
    SetConsoleScreenBufferSize(hOut, size);//point

    // ���ؿ���̨���
    GetConsoleCursorInfo(hOut, &CursorInfo);//��ȡ����̨�����Ϣ
    CursorInfo.bVisible = false; //���ؿ���̨���
    SetConsoleCursorInfo(hOut, &CursorInfo);//���ÿ���̨���״̬

    DWORD res;       //���ڴ洢��ȡ��¼
    COORD pos;       //���ڴ洢��굱ǰλ��  
    
    DWORD next_game_tick=(DWORD)0;
    int loops;
    float interpolation;//����ȼ۵�֡��//��Ⱦ֡����Ԥ�����ֵʵ�ֵ�

    HWND cmd = GetConsoleWindow();//����̨���ھ��
    //�õ��豸�������豸���������������DC
    HDC hDC = GetDC(cmd);//��Ļ��ʾDC
    //������Ļ��ʾDC�����ڴ�DC�豸��������
    HDC dcMEM = CreateCompatibleDC(hDC);//�ڴ����DC
    MSG msg;
    int timerID = 1;//TimerID
    int period = 40;//40ms����һ��timer
    //UINT_PTR MyID1 = SetTimer(NULL, timerID, period, (TIMERPROC)&TimerProc);
    DWORD InNum = 0;//�������滺���������¼�������
    DWORD judge = 1;//������InNum�Ƚϴ�С
    //ת�����ͣ��Ժ��InputNum���ݸ�GetNumberOfConsoleInputEvents
    LPDWORD InputNum = &InNum;

    POINT p;//�������

    //��ʼ��inputRecord
    ReadConsoleInput(hIn, &inputRecord, 1, &res);       //��ȡ�����¼�
    for (;;)
    {   
        //���������¼���ʱ��ŵ���ReadConsoleInput
        //��ֹ����ͣ�����ȴ�������Ϣ�������ѭ������
        GetNumberOfConsoleInputEvents(hIn, InputNum);
        if (*InputNum >= judge)
        {
            ReadConsoleInput(hIn, &inputRecord, 1, &res);       //��ȡ�����¼�
        }
        pos = inputRecord.Event.MouseEvent.dwMousePosition;     //��õ�ǰ���λ��  
        GetCursorPos(&p);
        if (inputRecord.EventType == MOUSE_EVENT)     //�����ǰΪ����¼�  
        {
            if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//������
            {
                switch (flag)
                {
                case BEFORE_START://�������İ�ť�У���ʼ���������ɾͣ��˳������ã�����
                {
                    //SetConsoleCursorPosition(hOut, pos);//�ѹ���ƶ���posλ��
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
        //�����ǰ�¼��Ǽ����¼�
        else if (inputRecord.EventType == KEY_EVENT)
        {
            switch (flag)
            {
            case PLAYING_GAME:
            {
                if (inputRecord.Event.KeyEvent.wVirtualKeyCode == 0x57 && inputRecord.Event.KeyEvent.bKeyDown && hh.direction != 'W')
                {

                    //�û�������W
                    hh.jump();
                    inputRecord.Event.KeyEvent.wVirtualKeyCode = '0';//Ϊ��֪����ʱû�а�W���Ұ������ó������ڰ�0

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
            //BEFOR_START����Ϸ��ʼ����
            DrawBmp(hDC, dcMEM, newGame320180, newGame, 320, 180, isFirst);//�����ڴ�dc��
            DrawBmp(hDC, dcMEM, continue320180, continueGame, 320, 180, isFirst);//�����ڴ�dc��
            DrawBmp(hDC, dcMEM, achievement320180, achievement, 320, 180, isFirst);//�����ڴ�dc��
            break; 
        }
        case BEFORE_INIT:
        {
            next_game_tick = (DWORD)GetTickCount64();//���شӳ���ʼ���е����ڵ�ʱ��/ms
            //��ʼ��������λ�á�����
            hh.setX(windowsLenth / 8);
            hh.setY(3*windowsWidth / 5);
            hh.init();

            //��ʼ������λ�á�����
            coin1.init();
            
            flag = PLAYING_GAME;
            break;
        }
        case PLAYING_GAME:
        {
            //system("cls");
            //update���������ݣ������ѧϰ��Ϸ��ѭ�������Ƹ������ݺ���Ⱦ��Ƶ�ʣ�Ŀǰ��û��

            //������벻��Ҫ����ô�ߵ�֡�ʸ��£�ǰ������Ϊÿ��50֡
            loops = 0;
            while (GetTickCount64() > next_game_tick && loops < MAX_FRAMESKIP)
            {
                //hh�Ĳ�������upDate_Data ÿ�벻�಻�ٵر�����50��
                upDate_data(hh);
                //�˴���Ҫ���ϰ�������ȵ�update�����º�����
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
            
            //�����ؼ�
            DrawBmp(hDC, dcMEM, back16090, back, 160, 90, isFirst);

            //������ֵ
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
            //�����Ǹ��������죬�����Ǵ���������ɾȥ��
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
                
            //������
            if(hh.direction=='W')
                DrawBmp(hDC, dcMEM, jumpcan180320, hh, 180, 320, isFirst, interpolation);
            else
                DrawBmp(hDC, dcMEM, can180320, hh, 180, 320, isFirst, interpolation);
            
            //�˴����˹����⣬�����ģ��ϰ��������Ҳ����Ҫ��ֵԤ��
            DrawBmp(hDC, dcMEM, unrecyclable200200, unrecyclable, 200, 200, isFirst);
            if (coin1.getEatenState()==false)
                DrawBmp(hDC, dcMEM, coin12080, coin1, 120, 80, isFirst);

            isFirst = false;//�˴��޸�ΪisFirst��ֹ������Ϸ����
            break;
        }
        case ACHIEVEMENT_SHOW:
            DrawBmp(hDC, dcMEM, achievement16090, achievement_t, 160, 90, isFirst);
            //�����ذ�ť����Ȼ���ڳɾͽ�����
            DrawBmp(hDC, dcMEM, back16090, back, 160, 90, isFirst);

            break;
        }

        //�������ò��˽⣬��getmessage����peekmessage��ֹ������ѭ��
        PeekMessage(&msg, NULL, 0, 0,PM_NOREMOVE);
        if (msg.message == WM_TIMER)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        //���ڴ�dc�ϵĶ���һ���Ի�����ʾdc��
        BitBlt(hDC, 0, 0, windowsLenth, windowsWidth, dcMEM, 0, 0, SRCCOPY); //�˴���һ��������ΪhDC,�����ھ��

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