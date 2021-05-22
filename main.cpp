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
const int ACHIEVEMENT_SHOW = 3;
const int GAME_OVER = 4;

const int gravity = 2;//ģ������

const int TICKS_PER_SECOND = 50;//50֡ÿ��ĸ����ٶ�
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;//1000֡�����ʱ�䣿
const int MAX_FRAMESKIP = 5;//֡��������С����͵ı���

int windowsLenth1 = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� 1280���� */
int windowsWidth1 = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� 720���� */

int windowsLenth = 855;//ʵ�ʻ������Ŀ�� 855���� 
int windowsWidth = 480;//ʵ�ʻ������ĸ߶� 480����
                       
//������ʵ��̫�ã���Ϊÿ̨���Ե�ѹ����ֵ�в��죬����ʱ������ʵ��
//У��ϵ��->��bmp�����к�����������С��ֵ
double correctX = (double)windowsLenth / windowsLenth1;
double correctY = (double)windowsWidth / windowsWidth1;




//��������������
Can hh;
//������ť
Button newGame((windowsLenth1-240)/2, 4*windowsWidth1/15, 240, 125);
Button continueGame((windowsLenth1 - 240) / 2, 7 * windowsWidth1 / 15, 240, 125);
Button achievement((windowsLenth1 - 240)/2, 10 * windowsWidth1 / 15, 240, 125);
Button back(windowsLenth1-100, 0, 100, 60);
//��Ϸ�������ǰ�ť����������ûд��Ӧ���࣬Ŀǰʹ�ð�ť
Background backgroundPlayingGame(0, 0, 1280, 720);
Background backgroundInit(0, 0, 1280, 720);
Background backgroundOver(0, 0, 1280, 720);
//�������⣨���ܰ���һ�ණ����
Title lifeOfcan(50, 50, 90, 160);
Title achievement_t((windowsLenth1 - 240) / 2, windowsWidth1 / 15, 160, 90);
Title coin_t(2*windowsLenth1/ 3,  windowsWidth1 / 15, 60, 40);
//�����ϰ���
Barrier unrecyclable;
//������������
Coin coin1(1);
//����������ֵ����
Coin coin2(2);


static int flag = BEFORE_START;//������Ϸ״̬Ϊ��������Ϸǰ
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
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);//�ص�����

DWORD WINAPI Thread1(LPVOID);
int main()
{         
    //����ͼƬ��Դ���������һ��resource.cpp�ļ�ר�ż��ظ���ͼƬ��Դ
    //����
    HBITMAP can150250 = (HBITMAP)LoadImage(NULL, "can150250.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP jumpcan150250 = (HBITMAP)LoadImage(NULL, "jumpcan150250.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP overcan180320 = (HBITMAP)LoadImage(NULL, "overcan180320.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //��ť
    HBITMAP continue240125 = (HBITMAP)LoadImage(NULL, "continue240125.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP newGame240125 = (HBITMAP)LoadImage(NULL, "newGame240125.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP achievement240125 = (HBITMAP)LoadImage(NULL, "achievement240125.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP back10060 = (HBITMAP)LoadImage(NULL, "back10060.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //����������
    HBITMAP background= (HBITMAP)LoadImage(NULL, "background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP initBackground = (HBITMAP)LoadImage(NULL, "initBackground1280720.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP overBackground = (HBITMAP)LoadImage(NULL, "overBackground1280720.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP achievement16090 = (HBITMAP)LoadImage(NULL, "achievement16090.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP coin6040 = (HBITMAP)LoadImage(NULL, "coin6040.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //����
    HBITMAP unrecyclable130130 = (HBITMAP)LoadImage(NULL, "unrecyclable130130.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP coin12080= (HBITMAP)LoadImage(NULL, "coin12080.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP life4580 = (HBITMAP)LoadImage(NULL, "life4580.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HBITMAP plusLife100100 = (HBITMAP)LoadImage(NULL, "plusLife100100.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


    //���崰�ڻ�������Ϣ�ṹ��  
    CONSOLE_SCREEN_BUFFER_INFO csbi;
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
    SetWindowPos(hwnd, HWND_TOP, 0, 0, windowsLenth1, windowsWidth1, 0);

    //�ı��ߣ�˳�����������������������ã�����֮������ܲ�����
    //system("mode con cols=100 lines=30");

    //��Ϊ�̶����ڴ�С->������
    //RECT rc;
    //���cmd���ڶ�Ӧ����
    //GetWindowRect(hwnd, &rc); 
    //�ı�cmd���ڷ��
    //SetWindowLongPtr(hwnd,GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
    //��Ϊ����漰���߿�ı䣬�������SetWindowPos��������Ч��

    //��������ȫ��
    //SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_THICKFRAME);
    //SetWindowPos(hwnd,NULL, rc.left,rc.top,rc.right - rc.left, rc.bottom - rc.top, NULL);
   
    ////�̶����ڴ�С
    //MoveWindow(hwnd, rc.left, rc.top, 800, 515, TRUE); // 815 width, 515 height

    //ȡ������������֪����������һ�䣩->��point�Ǿ䲻����ɾ��
    SMALL_RECT rect = SizeOfWindow(hOut);
    COORD size = { rect.Right + 1,rect.Bottom + 1 };
    //���û�������С
    SetConsoleScreenBufferSize(hOut, size);//point
    GetConsoleScreenBufferInfo(hOut, &csbi);//���ڼ���ָ���Ŀ���̨��Ļ����������Ϣ
    //���ô���λ�úʹ�С
    //SetConsoleWindowInfo(hOut, true, &rect);
    

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
        //cout << "x:" << windowsLenth1 << "  y:" << windowsWidth1<<" ";

        //���������¼���ʱ��ŵ���ReadConsoleInput
        //��ֹ����ͣ�����ȴ�������Ϣ�������ѭ������
        GetNumberOfConsoleInputEvents(hIn, InputNum);
        if (*InputNum >= judge)
        {
            ReadConsoleInput(hIn, &inputRecord, 1, &res);       //��ȡ�����¼�
        }
        pos = inputRecord.Event.MouseEvent.dwMousePosition;     //��õ�ǰ���λ��  
        GetCursorPos(&p);
        ScreenToClient(hwnd, &p);    // �����ָ��λ��ת��Ϊ��������
        if (inputRecord.EventType == MOUSE_EVENT)     //�����ǰΪ����¼�  
        {
            if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//������
            {
                switch (flag)
                {
                case BEFORE_START://�������İ�ť�У���ʼ���������ɾͣ��˳������ã�����
                {

                   /* cout << " x:" << p.x << " y:" << p.y << endl;
                    cout << correctX*newGame.getX() << " " << correctY*newGame.getY() << endl;
                    cout << newGame.getLength() << endl;*/

                    //SetConsoleCursorPosition(hOut, pos);//�ѹ���ƶ���posλ��
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
        //�����ǰ�¼��Ǽ����¼�
        if (inputRecord.EventType == KEY_EVENT)
        {
            switch (flag)
            {
            case PLAYING_GAME:
            {
                if (inputRecord.Event.KeyEvent.wVirtualKeyCode == 0x57 && inputRecord.Event.KeyEvent.bKeyDown )
                {
                    //�û�������W
                    jumpFlagDown = true;
                    //inputRecord.Event.KeyEvent.wVirtualKeyCode = '0';//Ϊ��֪����ʱû�а�W���Ұ������ó������ڰ�0
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
            //BEFOR_START����Ϸ��ʼ����
            DrawBmp(hDC, dcMEM, newGame240125, newGame, 240, 125, isFirst);//�����ڴ�dc��
            DrawBmp(hDC, dcMEM, continue240125, continueGame, 240, 125, isFirst);//�����ڴ�dc��
            DrawBmp(hDC, dcMEM, achievement240125, achievement, 240, 125, isFirst);//�����ڴ�dc��
            break; 
        }
        case BEFORE_INIT:
        {
            next_game_tick = (DWORD)GetTickCount64();//���شӳ���ʼ���е����ڵ�ʱ��/ms
            //��ʼ��������λ�á�����
            hh.init();

            //��ʼ������λ�á�����
            coin1.init();
            coin2.init();

            //��ʼ���ϰ���λ�á�����
            unrecyclable.init();
            
            flag = PLAYING_GAME;
            break;
        }
        case PLAYING_GAME:
        {
            //system("cls");
            //update���������ݣ������ѧϰ��Ϸ��ѭ�������Ƹ������ݺ���Ⱦ��Ƶ�ʣ�Ŀǰ��û��
            if(jumpFlagDown)
            {
                jumpFlagEver = true;
            }
            
            //������벻��Ҫ����ô�ߵ�֡�ʸ��£�ǰ������Ϊÿ��50֡
            loops = 0;
            while (GetTickCount64() > next_game_tick && loops < MAX_FRAMESKIP)
            {
                //hh�Ĳ�������upDate_Data ÿ�벻�಻�ٵر�����50��
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

                //��ֹcan���µ�
                if (jumpFlagEver && !jumpFlagDown && hh.direction != 'W')
                {
                    hh.jump();
                    jumpFlagEver = false;
                }

                next_game_tick += SKIP_TICKS;
                loops++;
            }
            interpolation = float(GetTickCount64() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);
            
            //�����ؼ�
            DrawBmp(hDC, dcMEM, back10060, back, 100, 60, isFirst);

            //������ֵ
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

            //������ֵ
            DrawBmp(hDC, dcMEM, coin6040, coin_t, 60, 40, isFirst);
            //ָ��λ��������֣��ƶ���ĳ��λ������ĺ����Ҳ��ǵ���
            
                
            //�����ӣ���������վ�ŵ�����״̬��
            if(hh.direction=='W')
                DrawBmp(hDC, dcMEM, jumpcan150250, hh, 150, 250, isFirst, interpolation);
            else
                DrawBmp(hDC, dcMEM, can150250, hh, 150, 250, isFirst, interpolation);
            
            //�˴����˹����⣬�����ģ��ϰ��������Ҳ����Ҫ��ֵԤ��
            DrawBmp(hDC, dcMEM, unrecyclable130130, unrecyclable, 200, 200, isFirst);
            if (coin1.getEatenState()==false)
                DrawBmp(hDC, dcMEM, coin12080, coin1, 120, 80, isFirst);
            if (coin2.getEatenState() == false)
                DrawBmp(hDC, dcMEM, plusLife100100, coin2, 100, 100, isFirst);

            isFirst = false;//�˴�isFirst��ֵΪfalse��ֹ������Ϸ����
            
            if (hh.getLife() <= 0)
                flag = GAME_OVER;
            break;
        }
        case ACHIEVEMENT_SHOW:
            DrawBmp(hDC, dcMEM, achievement16090, achievement_t, 160, 90, isFirst);
            //�����ذ�ť����Ȼ���ڳɾͽ�����
            DrawBmp(hDC, dcMEM, back10060, back, 100, 60, isFirst);
            break;
        case GAME_OVER:
            //GAME_OVER����Ϸ��������
            DrawBmp(hDC, dcMEM, overBackground, backgroundOver, 1280, 720, true);
            isFirst = false;
            hh.setX(windowsLenth / 2);
            hh.setY(2*windowsWidth1 / 5);
            //�����ϵ����Ǻͷ��ؼ�
            DrawBmp(hDC, dcMEM, overcan180320, hh, 180, 320, isFirst);
            DrawBmp(hDC, dcMEM, back10060, back, 100, 60, isFirst);
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
        BitBlt(hDC, 0, 0, windowsLenth1, windowsWidth1, dcMEM, 0, 0, SRCCOPY); //�˴���һ��������ΪhDC,�����ھ��

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