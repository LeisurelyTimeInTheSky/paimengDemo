#pragma once

extern int WINDOW_WIDTH;	// ÆÁÄ»¿í¶È
extern int WINDOW_HEIGHT;	// ÆÁÄ»¸ß¶È

#pragma comment(lib,"Winmm.lib")
#pragma comment(lib, "MSIMG32.LIB")

inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
