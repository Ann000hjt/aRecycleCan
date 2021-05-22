#pragma once
class Object;
class Can;
HDC DrawBmp(HDC hDC, HDC dcMEM, HBITMAP hBitmap, Object& object, int bmpLenth, int bmpWidth,bool isFirst);
HDC DrawBmp(HDC hDC, HDC dcMEM, HBITMAP hBitmap, Can& can, int bmpLenth, int bmpWidth,bool isFirst, float interpolation);