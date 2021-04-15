
#include"Column.h"




Column::Column()
{

	this->heightOfBottomColumn = rand() % 100 + 50;//���50-149
	this->gapOfTwoColumn = rand() % 50 + 100;//
	this->xCol = windowsLenth - widthOfColumn;
	this->yCol = windowsWidth - this->heightOfBottomColumn;



}



void drawCol(int LTX, int LTY, int RBX, int RBY)
{
	HWND hwnd = GetForegroundWindow(); //�ҵ��������д��ڵľ��
	HDC hDC = GetDC((HWND)hwnd);//ͨ�����ھ���õ��ô��ڵ��豸�������
	HPEN hPen; //����
	HBRUSH hBrush;

	hPen = CreatePen(PS_SOLID, 0, 0xff0000);
	hBrush = CreateSolidBrush(RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);


	Rectangle(hDC, LTX, LTY, RBX, RBY);


	hPen = (HPEN)SelectObject(hDC, oldPen);
	hBrush = (HBRUSH)SelectObject(hDC, oldBrush);


	DeleteObject(hPen);
	DeleteObject(hBrush);
	DeleteObject(oldPen);
	DeleteObject(oldBrush);
	ReleaseDC(hwnd, hDC);
}

Column& Column::operator=(Column right)
{
	this->xCol = right.xCol;

	return *this;
}

void Column::drawColumn()
{
		drawCol(this->xCol, this->yCol, this->xCol + this->widthOfColumn, windowsWidth);//draw bottom rec
		drawCol(this->xCol, 0, this->xCol + this->widthOfColumn, this->yCol - this->gapOfTwoColumn);//draw top rec
}
void Column::moveColumn()//move position of Column over time
{
		this->xCol += vx;
}
void Column::changeColumn()
{
	srand((unsigned int)time(NULL));
	
		if (this->xCol <= -20)
		{
			this->xCol = windowsLenth - this->widthOfColumn;
			this->heightOfBottomColumn = rand() % 100 + 50;//���50-149
			this->gapOfTwoColumn = rand() % 50 + 100;//
			this->yCol = windowsWidth - this->heightOfBottomColumn;
		}
	
}