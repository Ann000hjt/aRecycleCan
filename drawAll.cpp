
#include<Windows.h>
#include"drawAll.h"

#include"Object.h"

extern int windowsLenth;
extern int windowsWidth;





HDC DrawBmp(HDC dcMEM, HBITMAP hBitmap, Object & object,int bmpLenth ,int bmpWidth)
{

    HBITMAP continue320180 = (HBITMAP)LoadImage(NULL, "continue320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HDC dcTemp;
    dcTemp = CreateCompatibleDC(dcMEM);//����һ���ڴ�DC
    //������hDC������ص��豸���ݵ�λͼ
    
    //HBITMAP bmpBackground = CreateCompatibleBitmap(dcTemp, windowsLenth, windowsWidth);//�����ֱ�Ϊ��hDC��λͼ����λͼ��
    // 
    //����delete dcTemp������������滻��hBitmap�Ļ���deleteʱ���hBitmapһ��ɾ��
    //����ֵ�Ǳ�ȡ������ľ��//����ɵľ��������ָ�ԭ״
    HBITMAP hOldBmp = (HBITMAP)SelectObject(dcTemp, continue320180);//λͼѡ����ڴ�DC
    SelectObject(dcTemp, continue320180);
    //SelectObject(dcTemp, bmpBackground);
    //SelectObject(hdcMEM, hBitmap);

    //StretchBlt(hdcMEM, 0, 0, 100, 100, hdcImage, 0, 0, 100, 100, SRCCOPY); //�������������ͼ����hdcImage�е�λͼֱ�Ӹ��Ƶ��ڴ滺����

    //StretchBlt(hDC, object.getX(), object.getY(), bmpLenth, bmpWidth, hdcMEM, object.getX(), object.getY(), bmpLenth, bmpWidth, SRCCOPY); //�ٽ��ڴ滺�����е����ݻ��Ƶ���Ļ��.
    BitBlt(dcMEM, object.getX() - (bmpLenth / 2), object.getY() - (bmpWidth / 2), bmpLenth, bmpWidth, dcTemp, 0, 0, SRCCOPY);


    //StretchBlt(hdcMEM, LTX, LTY, RBX, RBY, hdcMEM, LTX, LTY, RBX, RBY, SRCCOPY); //�������������ͼ����hdcImage�е�λͼֱ�Ӹ��Ƶ��ڴ滺����
    //StretchBlt(hDCtemp, LTX, LTY, RBX, RBY, hdcMEM, LTX, LTY, RBX, RBY, SRCCOPY); //�ٽ��ڴ滺�����е����ݻ��Ƶ���Ļ��.

    //�ָ�ԭ״
    SelectObject(dcTemp, hOldBmp);
    //ɾ��dc
    DeleteDC(dcTemp);

    return dcMEM;

}