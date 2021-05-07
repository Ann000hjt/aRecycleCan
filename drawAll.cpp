#include<Windows.h>
#include"drawAll.h"
#include"Object.h"
extern int windowsLenth;
extern int windowsWidth;
HDC DrawBmp(HDC hDC,HDC dcMEM, HBITMAP hBitmap, Object & object,int bmpLenth ,int bmpWidth)
{
    //dcMEM是和屏幕显示DC兼容的内存DC
    HDC dcTemp;
    dcTemp = CreateCompatibleDC(hDC);//创建一个内存DC
    //创建与hDC环境相关的设备兼容的位图
    //此处使用hDC(窗口DC)Create位图，否则图片只有黑白两色
    HBITMAP bmpBackground = CreateCompatibleBitmap(hDC, windowsLenth, windowsWidth);//参数分别为：hDC，位图长，位图宽
    //内存dc一号(dcMEM)select背景图片
    SelectObject(dcMEM, bmpBackground);
    //便于delete dcTemp，如果不用他替换掉hBitmap的话，delete时会把hBitmap一起删掉
    //返回值是被取代对象的句柄//保存旧的句柄，方便恢复原状
    //内存dc二号(dcTemp)select要画的图片
    HBITMAP hOldMap=(HBITMAP)SelectObject(dcTemp, hBitmap);//位图选择进内存DC
    //把dcTemp里的图画到dcMEM上
    BitBlt(dcMEM, object.getX(), object.getY(), bmpLenth, bmpWidth, dcTemp, 0, 0, SRCCOPY);
    //恢复原状
    SelectObject(dcTemp, hOldMap);
    //删除dc
    DeleteDC(dcTemp);
    return dcMEM;
}