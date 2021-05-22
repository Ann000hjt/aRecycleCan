#pragma once
#include"Object.h"
bool isKickRect(int kick_x, int kick_y, int Rect_x, int Rect_y, int Rect_length, int Rect_width, int narrow);
//因为检测矩形大小与按钮大小一样的时候 会出现周围也可以通过的情况 所以我加了一个narrow代表长宽缩小的值
//Rect_x和Rect_y是矩形的中心位置
bool isKickButton(int kick_x, int kick_y, Button button, int narrow);
bool isCoinEaten(Can& can, Coin& coin);
bool isBarrierCrush(Can& can, Barrier& barrier);