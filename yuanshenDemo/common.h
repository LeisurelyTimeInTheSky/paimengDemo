#pragma once
#include "Atlas.h"

extern int WINDOW_WIDTH;	// 屏幕宽度
extern int WINDOW_HEIGHT;	// 屏幕高度

const int BUTTON_WIDTH = 192;	// 按钮宽度
const int BUTTON_HEIGHT = 75;	// 按钮高度

#pragma comment(lib,"Winmm.lib")
#pragma comment(lib, "MSIMG32.LIB")

inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}


extern Atlas* atlas_player_left;
extern Atlas* atlas_player_right;
extern Atlas* atlas_enemy_left;
extern Atlas* atlas_enemy_right;


extern bool is_game_started;
extern bool isRunning;