// v.0.3-04.12.22

#pragma once
#include <wtypes.h>

class SelFrame
{
	BOOL result;
	HPEN LBLinePen, RBLinePen;
	TRACKMOUSEEVENT tme;
	HWND hw;
	unsigned char LB_status, RB_status;
	RECT rect;
	signed char ObjectMode;
	BOOL SkipLBRect, LBDisabled, SkipRBRect, RBDisabled;

public:
	int MouseLBX1, MouseLBY1, MouseLBX2, MouseLBY2, MouseRBX1, MouseRBY1, MouseRBX2, MouseRBY2;
	SelFrame();						// конструктор класса
	void init(HWND HW);
	void wm_lbuttondown(int, int);
	void wm_lbuttonup(int, int);
	void wm_rbuttondown(int, int);
	void wm_rbuttonup(int, int);
	void wm_paint(HDC hdc);
	void wm_mousemove(int mouseX, int mouseY);
	void wm_mouseleave();
	void SetMode(signed char ObjectMode);
};

