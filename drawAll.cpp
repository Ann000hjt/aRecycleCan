#include<Windows.h>
#include"drawAll.h"
#include"Object.h"
extern int windowsLenth;
extern int windowsWidth;
HDC DrawBmp(HDC hDC,HDC dcMEM, HBITMAP hBitmap, Object & object,int bmpLenth ,int bmpWidth)
{
    //dcMEM�Ǻ���Ļ��ʾDC���ݵ��ڴ�DC
    HDC dcTemp;
    dcTemp = CreateCompatibleDC(hDC);//����һ���ڴ�DC
    //������hDC������ص��豸���ݵ�λͼ
    //�˴�ʹ��hDC(����DC)Createλͼ������ͼƬֻ�кڰ���ɫ
    HBITMAP bmpBackground = CreateCompatibleBitmap(hDC, windowsLenth, windowsWidth);//�����ֱ�Ϊ��hDC��λͼ����λͼ��
    //�ڴ�dcһ��(dcMEM)select����ͼƬ
    SelectObject(dcMEM, bmpBackground);
    //����delete dcTemp������������滻��hBitmap�Ļ���deleteʱ���hBitmapһ��ɾ��
    //����ֵ�Ǳ�ȡ������ľ��//����ɵľ��������ָ�ԭ״
    //�ڴ�dc����(dcTemp)selectҪ����ͼƬ
    HBITMAP hOldMap=(HBITMAP)SelectObject(dcTemp, hBitmap);//λͼѡ����ڴ�DC
    //��dcTemp���ͼ����dcMEM��
    BitBlt(dcMEM, object.getX(), object.getY(), bmpLenth, bmpWidth, dcTemp, 0, 0, SRCCOPY);
    //�ָ�ԭ״
    SelectObject(dcTemp, hOldMap);
    //ɾ��dc
    DeleteDC(dcTemp);
    return dcMEM;
}