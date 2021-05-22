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
//����200ms
#define half 200

using namespace std;

const int BEFORE_START = 0;
const int BEFORE_INIT = 1;
const int PLAYING_GAME = 2;

const int gravity = 2;//ģ������

const int TICKS_PER_SECOND = 50;//50֡ÿ��ĸ����ٶ�
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;//1000֡�����ʱ�䣿
const int MAX_FRAMESKIP = 5;//֡��������С����͵ı���

int windowsLenth = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
int windowsWidth = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */

Can hh;//��������������
//������ť
Button startGame(windowsLenth / 2, 3 * windowsWidth / 8, 320, 180);
Button continueGame(windowsLenth / 2, 5 * windowsWidth / 8, 320, 180);
//��Ϸ�������ǰ�ť����������ûд��Ӧ���࣬Ŀǰʹ�ð�ť
Button backgroundPlayingGame(0, 0, windowsLenth, windowsWidth);
//�����ϰ���
Barrier unrecyclable;
//��������
Coin coin1;

static int flag = BEFORE_START;//������Ϸ״̬Ϊ��������Ϸǰ

bool isFirst = true;


SMALL_RECT SizeOfWindow(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &info);
    return info.srWindow;
}
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);//�ص�����
DWORD WINAPI Thread1(LPVOID);
int main()
{         
    //���崰�ڻ�������Ϣ�ṹ��  
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    //����ͼƬ��Դ���������һ��resource.cpp�ļ�ר�ż��ظ���ͼƬ��Դ
    HBITMAP continue320180 = (HBITMAP)LoadImage(NULL, "continue320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP newGame320180 = (HBITMAP)LoadImage(NULL, "newGame320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP can180320 = (HBITMAP)LoadImage(NULL, "can180320.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP unrecyclable200200 = (HBITMAP)LoadImage(NULL, "unrecyclable200200.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP background= (HBITMAP)LoadImage(NULL, "background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
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


    HANDLE hThread;
    DWORD threadID;
    hThread = CreateThread(NULL, 0, Thread1, 0, 0, &threadID);//��������






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
                    if(isKickButton(p.x,p.y,startGame,8))
                    {
                        isFirst = true;
                        //KillTimer(NULL, MyID1);
                        flag = BEFORE_INIT;
                    }
                    break;
                }
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
            DrawBmp(hDC,dcMEM, newGame320180, startGame, 320, 180, isFirst);//�����ڴ�dc��
            DrawBmp(hDC, dcMEM, continue320180, continueGame, 320, 180, isFirst);//�����ڴ�dc��
            break; 
        }
        case BEFORE_INIT:
        {
            next_game_tick = GetTickCount64();//���شӳ���ʼ���е����ڵ�ʱ��/ms
            //�ı�������λ�ã���Ȼ������ʹ��continue��ͼ���ݴ�����������
            hh.setX(windowsLenth / 8);
            hh.setY(3*windowsWidth / 5);
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
                next_game_tick += SKIP_TICKS;
                loops++;
            }
            interpolation = float(GetTickCount64() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);
            //draw
            DrawBmp(hDC,dcMEM, can180320, hh, 180, 320, isFirst,interpolation);
            //�˴����˹����⣬�����ģ��ϰ��������Ҳ����Ҫ��ֵԤ��
            DrawBmp(hDC, dcMEM, unrecyclable200200, unrecyclable, 200, 200, isFirst);
            DrawBmp(hDC, dcMEM, unrecyclable200200, coin1, 200, 200, isFirst);
            isFirst = false;
            break;
        }

        }
        //�������ò��˽⣬��getmessage����peekmessage��ֹ������ѭ��
        PeekMessage(&msg, NULL, 0, 0,PM_NOREMOVE);
        if(msg.message == WM_TIMER)
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
DWORD WINAPI Thread1(LPVOID)//���̺������������ű�������
{
    int tiger2[][2] =
    {
        {do,2},{re,2},{mi,2},{do,2},//��ֻ�ϻ�
        {re,2},{so,2},{so,2},{0,2},//������
        {mi,2},{la,1},{la,1},{la,2},{la,2},//С���ӹԹ�
        {so,1},{mi,1},{so,2},{mi,2},{0,2},//���ܲ�
        {do,3},{do,1},{do,2},{la,1},{la,1},//�Һ�СѼ��
        {so,2},{mi,2},{so,2},{0,2},//ѧ��·
        {re,1},{re,2},{mi,1},{mi,1},{re,1},{do,1},{mi,1},//ͯ������������
        {re,4},{qso,1},{qla,1},{qsi,1},{re,1},//��
        {do,2},{re,2},{mi,2},{do,2},//С�ݺ�ѽ
        {re,2},{so,1},{so,1},{so,2},{0,2},//�εεش�
        {mi,2},{la,2},{la,2},{do1,2},//��ѧ��Ÿ
        {si,2},{la,2},{so,2},{0,2},//չ���
        {do,3},{do,1},{do,2},{la,2},//���·���
        {so,2},{so,2},{mi,2},{0,2},//������
        {re,1},{re,2},{mi,1},{mi,1},{re,1},{do,1},{re,1},//���ѱ��춼ѧ
        {do,4},{do,1},{re,1},{mi,1},{so,1},//��,��
        {do1,3},{do1,1},{do1,1},{so,1},{mi,1},{do1,1},//��������Ϊ��ָ
        {si,4},{0,2},{0,1},{mi,1},//·����
        {la,3},{la,1},{la,1},{so,1},{la,1},{si,1},//��������Ϊ��ף
        {so,4},{0,2},{0,2},//��
        {mi,2},{so,1},{so,1}, {so,2},{do1,2},//�ɳ��ǿ���
        {re1,3},{re1,1},{la,4},//����;
        {so,1},{so,1},{so,1}, {la,1},{si,1}, {la,1},{si,1}, {do1,1},//�¸�������Ľ�
        {re1,6},{0,1},{so,1},//������
        {do1,3},{do1,1},{do1,1},{so,1},{mi,1},{do1,1},//�������軳�ﰲ
        {si,4},{0,2},{0,1},{mi,1},//˯����
        {la,3},{la,1},{la,1},{so,1},{la,1},{si,1},//�ְ�������
        {so,4},{0,2},{0,2},//��
        {mi,2},{so,2},{so,2},{do1,1},{do1,1},//�������ǵ�
        {re1,1},{re1,1},{re1,2},{la,4},//�ĸα���
        {so,1},{so,1},{so,1},{la,1},{si,1},{do1,1},{do1,1},{re1,1},//�ְ�����İ�����
        {do1,8},//��
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