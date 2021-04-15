#include<Windows.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>

#include"Object.h"

const int BEFORE_START = 0;
const int BEFORE_INIT = 1;
const int PLAYING_GAME = 2;

const int vx = -8;//column speed
const int gravity = 3;
const int radius = 10;

int windowsLenth = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
int windowsWidth = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */

Can hh;
const int Num = 4;

static int flag = 0;

SMALL_RECT SizeOfWindow(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &info);
    return info.srWindow;
}
void showMenu(HANDLE screen);
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
HDC DrawBmp(HDC hDCtemp, HBITMAP hBitmap,int LTX, int LTY,int RBX, int RBY)
{
    HDC hdcMEM; 
    hdcMEM = CreateCompatibleDC(hDCtemp);

    SelectObject(hdcMEM, hBitmap);//ע��˴�����Ҫ����λͼѡ��hdcImage

    StretchBlt(hdcMEM, LTX, LTY, RBX, RBY, hdcMEM, LTX, LTY, RBX, RBY, SRCCOPY); //�������������ͼ����hdcImage�е�λͼֱ�Ӹ��Ƶ��ڴ滺����
    StretchBlt(hDCtemp, LTX, LTY, RBX, RBY, hdcMEM, LTX, LTY, RBX, RBY, SRCCOPY); //�ٽ��ڴ滺�����е����ݻ��Ƶ���Ļ��.

    DeleteObject(hdcMEM);
    return hDCtemp;

}
int main()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;         //���崰�ڻ�������Ϣ�ṹ��  

    HANDLE	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//��ñ�׼�����豸���
    HANDLE	hIn = GetStdHandle(STD_INPUT_HANDLE);//��ñ�׼����豸���
    INPUT_RECORD mouserec;       //���������¼��ṹ��  

    DWORD mode;
    GetConsoleMode(hIn, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;  //�Ƴ����ٱ༭ģʽ
    mode &= ~ENABLE_INSERT_MODE;      //�Ƴ�����ģʽ
    //mode &= ~ENABLE_MOUSE_INPUT;??
    SetConsoleMode(hIn, mode);

    HWND hwnd = GetForegroundWindow();

    int windowsLenth = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
    int windowsWidth = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */
    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* ��ȡ������Ϣ */

    //std::cout << "x" << cx << std::endl;
   // std::cout << "y" << cy << std::endl;
    //��������ȫ��
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_THICKFRAME);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, windowsLenth, windowsWidth, 0);
    // & ~WS_BORDER & ~WS_CAPTION
    //ȡ��������
    GetConsoleScreenBufferInfo(hOut, &csbi);
    SMALL_RECT rect = SizeOfWindow(hOut);
    COORD size = { rect.Right + 1,rect.Bottom + 1 }; //���建������С 
    SetConsoleScreenBufferSize(hOut, size);//point
    /*std::cout << "right" << rect.Right << std::endl;
    std::cout << "Bottom" << rect.Bottom << std::endl;
    std::cout << "Left" << rect.Left << std::endl;
    std::cout << "Top" << rect.Top << std::endl;*/
    DWORD res;       //���ڴ洢��ȡ��¼  
    COORD pos;       //���ڴ洢��굱ǰλ��  



    MSG msg;
    UINT_PTR MyIDMenu = SetTimer(NULL, 1, 1, &TimerProc);
    DWORD InNum = 0;
    DWORD judge = 1;
    LPDWORD InputNum = &InNum;

    POINT p;//�������
    showMenu(hOut);
    ReadConsoleInput(hIn, &mouserec, 1, &res);       //��ȡ�����¼�
    for (;;)
    {
        GetNumberOfConsoleInputEvents(hIn, InputNum);
        if (*InputNum >= judge)
        {
            ReadConsoleInput(hIn, &mouserec, 1, &res);       //��ȡ�����¼�
        }
        pos = mouserec.Event.MouseEvent.dwMousePosition;     //��õ�ǰ���λ��  
        GetCursorPos(&p);

        

        if (mouserec.EventType == MOUSE_EVENT)     //�����ǰΪ����¼�  
        {
            if (mouserec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                //std::cout << p.x << std::endl << p.y << std::endl;
                switch (flag)
                {
                case 0:
                {
                    //SetConsoleCursorPosition(hOut, pos);//�ѹ���ƶ���posλ��
                    //std::cout << "x: " << p.x << "y: " << p.y << std::endl;
                    if (p.x > (windowsLenth / 2) - 160&& p.x < (windowsLenth / 2) + 160 && p.y > (3 * windowsWidth / 5) - 90 && p.y < (3 * windowsWidth / 5) + 90)
                    {
                        system("cls");
                        //KillTimer(NULL, MyIDMenu);
                        flag = BEFORE_INIT;
                    }
                    break;
                }
                default:
                    break;
                }
            }
        }
        switch (flag)
        {
        case 0:
            break;
        case 1:
        {
            //showMenu(hOut);
            flag = PLAYING_GAME;
            break;
        }
        case 2:
        {
            //system("cls");
            hh.draw();
            Sleep(50);
            break;
        }
        }
        PeekMessage(&msg, NULL, 0, 0,PM_NOREMOVE);
            if(msg.message == WM_TIMER)
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        
    }

    CloseHandle(hOut);
    CloseHandle(hIn);

    return 0;

}
void showMenu(HANDLE screen)
{

    int cx = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
    int cy = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */

    HMODULE hKernel32 = GetModuleHandle("kernel32");
    HWND cmd = GetConsoleWindow();//����̨���ھ��

    HDC dc = GetDC(cmd);
    HBITMAP hBitmap;
    HDC cmdmem = CreateCompatibleDC(dc);
    hBitmap = (HBITMAP)LoadImage(NULL, "continue320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);



    SelectObject(cmdmem, hBitmap);

    int buttonStartWidth = 320;
    int buttonStartHeight = 180;

    BitBlt(dc, (cx / 2), (3*cy / 5), buttonStartWidth, buttonStartHeight, cmdmem, 0, 0, SRCCOPY);

    return;
}
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    HANDLE	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//��ñ�׼�����豸���
//WM_TIMER

}