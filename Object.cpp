#include"Object.h"


const int vx = -8;//column speed
const int gravity = 3;
const int radius = 10;

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


//    //move����һ��ѭ����������
//    char c = _getch();
//    switch (c)
//    {
//    case 13://�س���
//        cout << "wait..." << endl;
//        system("pause");
//        //������� ��������ͣ��Ϸ flag=
//        break;
//    case 80://����
//        direction = 'S';
//        break;
//    case 72://����
//        if (direction != 'W')v_y = 1;//�ٶ��ȼ�����1����������Ѿ������Ͼ�����Ч����
//        direction = 'W';
//        break;
//    case 75://����
//        direction = 'A';
//        v_x = -1;//����λ�Ƶ�ʱ����������ʽ
//        this->x--;
//        break;
//    case 77://����
//        direction = 'D';
//        v_x = 1;
//        this->x += 1;//ͨ����������ÿһ�μӵ�ֵ��ʵ���ٶȵĿ���
//        break;
//    default:
//        break;
//    }
}
void Can::draw()
{
    //can��һ��λͼ
    //HMODULE hKernel32 = GetModuleHandle("kernel32");
    //HWND cmd = GetConsoleWindow();//����̨���ھ��

    //HDC dc = GetDC(cmd);




    //HBITMAP hBitmap;
    ////HDC cmdmem = CreateCompatibleDC(dc);
    //// 
    //HDC hdcMEM;
    //hdcMEM = CreateCompatibleDC(hDCtemp);
    ////if (this->direction == 'A')
    ////{
    ////    hBitmap = (HBITMAP)LoadImage(NULL, "left.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    ////}
    ////else
    ////{
    ////    hBitmap = (HBITMAP)LoadImage(NULL, "right.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    ////}
    //hBitmap = (HBITMAP)LoadImage(NULL, "continue320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    //SelectObject(hdcMEM, hBitmap);

    //int buttonStartWidth = 320;
    //int buttonStartHeight = 180;

    //BitBlt(dc,x ,y, buttonStartWidth, buttonStartHeight, cmdmem, 0, 0, SRCCOPY);
}

void Can::changeState()
{
    //�������ΪW����������������̣������䵽�����ˣ��������ΪD
    if (direction == 'W' && v_y > 0 && y == 4 * windowsWidth / 5)
    {
        this->direction = 'D';
    }


}