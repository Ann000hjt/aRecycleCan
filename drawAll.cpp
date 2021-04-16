
#include<Windows.h>
#include"drawAll.h"

#include"Object.h"

extern int windowsLenth;
extern int windowsWidth;





HDC DrawBmp(HDC dcMEM, HBITMAP hBitmap, Object & object,int bmpLenth ,int bmpWidth)
{

    HBITMAP continue320180 = (HBITMAP)LoadImage(NULL, "continue320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HDC dcTemp;
    dcTemp = CreateCompatibleDC(dcMEM);//创建一个内存DC
    //创建与hDC环境相关的设备兼容的位图
    
    //HBITMAP bmpBackground = CreateCompatibleBitmap(dcTemp, windowsLenth, windowsWidth);//参数分别为：hDC，位图长，位图宽
    // 
    //便于delete dcTemp，如果不用他替换掉hBitmap的话，delete时会把hBitmap一起删掉
    //返回值是被取代对象的句柄//保存旧的句柄，方便恢复原状
    HBITMAP hOldBmp = (HBITMAP)SelectObject(dcTemp, continue320180);//位图选择进内存DC
    SelectObject(dcTemp, continue320180);
    //SelectObject(dcTemp, bmpBackground);
    //SelectObject(hdcMEM, hBitmap);

    //StretchBlt(hdcMEM, 0, 0, 100, 100, hdcImage, 0, 0, 100, 100, SRCCOPY); //这里才能正常画图，将hdcImage中的位图直接复制到内存缓冲区

    //StretchBlt(hDC, object.getX(), object.getY(), bmpLenth, bmpWidth, hdcMEM, object.getX(), object.getY(), bmpLenth, bmpWidth, SRCCOPY); //再将内存缓冲区中的数据绘制到屏幕上.
    BitBlt(dcMEM, object.getX() - (bmpLenth / 2), object.getY() - (bmpWidth / 2), bmpLenth, bmpWidth, dcTemp, 0, 0, SRCCOPY);


    //StretchBlt(hdcMEM, LTX, LTY, RBX, RBY, hdcMEM, LTX, LTY, RBX, RBY, SRCCOPY); //这里才能正常画图，将hdcImage中的位图直接复制到内存缓冲区
    //StretchBlt(hDCtemp, LTX, LTY, RBX, RBY, hdcMEM, LTX, LTY, RBX, RBY, SRCCOPY); //再将内存缓冲区中的数据绘制到屏幕上.

    //恢复原状
    SelectObject(dcTemp, hOldBmp);
    //删除dc
    DeleteDC(dcTemp);

    return dcMEM;

}