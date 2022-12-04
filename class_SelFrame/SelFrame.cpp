// v.0.2-04.12.22

#include "SelFrame.h"
#include <tchar.h>

SelFrame::SelFrame()
{
	result = FALSE;							// ���� �� ��������������
	// ����� ������� � ���� ��-��������� ��� ����� �� ���
	LBLinePen = CreatePen(PS_SOLID,         // ����������� �����
		                  0,                // ������� ����� - 1 ������
		                  RGB(255, 0, 0));  // ���� ����� �� ��� - �������
	// ����� ������� � ���� ��-��������� ��� ����� �� ���
	RBLinePen = CreatePen(PS_DASH,         // ���������� �����
		                  0,                // ������� ����� - 1 ������
		                  RGB(0, 255, 0));  // ���� ����� �� ��� - ������
	tme = { 0,0,0,0 };						// ���� �� ��������������
	hw = 0;									// ���� �� ��������������
	LB_status = 0;
	RB_status = 0;
	rect = { 0,0,0,0 };						// ���� �� ��������������
	ObjectMode = 1;							// ����������� � ������������ ��� ��
	SkipLBRect = FALSE;
	LBDisabled = FALSE;
	SkipRBRect = FALSE;
	RBDisabled = FALSE;
	MouseLBX1 = MouseLBY1 = 0;
	MouseLBX2 = MouseLBY2 = 0;
	MouseRBX1 = MouseRBY1 = 0;
	MouseRBX2 = MouseRBY2 = 0;
}

void SelFrame::init(HWND HW)
{
	hw = HW;
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = hw;
	tme.dwFlags = TME_LEAVE;
	tme.dwHoverTime = HOVER_DEFAULT;
}


void SelFrame::wm_lbuttondown(int mouseXLB, int mouseYLB)
{
	if (LBDisabled || RB_status >= 1) return;
	MouseLBX1 = mouseXLB;
	MouseLBY1 = mouseYLB;
	MouseLBX2 = 0;
	MouseLBY2 = 0;
	LB_status = 1;	// ������ ��� - ������
//-\/ otladka
	rect = { 4,0,150,160 }; // ������� ������ ��������� �������
	InvalidateRect(0, &rect, TRUE);
//-/\ otladka
};

void SelFrame::wm_lbuttonup(int mouseXLB, int mouseYLB)
{
	if (LBDisabled || RB_status >= 1) return;
	MouseLBX2 = mouseXLB;
	MouseLBY2 = mouseYLB;
	LB_status = 0;	// ������ ��� - ��������
//-\/ otladka
	rect = { 4,0,150,160 };
	InvalidateRect(0, &rect, TRUE);
//-/\ otladka
};

void SelFrame::wm_rbuttondown(int mouseXRB, int mouseYRB)
{
	if (RBDisabled || LB_status >= 1) return;
	MouseRBX1 = mouseXRB;
	MouseRBY1 = mouseYRB;
	MouseRBX2 = 0;
	MouseRBY2 = 0;
	RB_status = 1;	// ������ ��� - ������
//-\/ otladka
	rect = { 4,0,150,160 };
	InvalidateRect(0, &rect, TRUE);
//-/\ otladka
};

void SelFrame::wm_rbuttonup(int mouseXRB, int mouseYRB)
{
	if (RBDisabled || LB_status >= 1) return;
	MouseRBX2 = mouseXRB;
	MouseRBY2 = mouseYRB;
	RB_status = 0;	// ������ ��� - ��������
//-\/ otladka
	rect = { 4,0,150,160 };
	InvalidateRect(0, &rect, TRUE);
//-/\ otladka
};

void SelFrame::wm_paint(HDC hdc)
{
//*\/ otladka
	wchar_t wCh[100];
	RECT rect1 = { 4,0,150,20 };
	RECT rect2 = { 4,20,150,40 };
	RECT rect3 = { 4,40,150,60 };
	RECT rect4 = { 4,60,150,80 };
	RECT rect5 = { 4,80,150,100 };
	RECT rect6 = { 4,100,150,120 };
	RECT rect7 = { 4,120,150,140 };
	RECT rect8 = { 4,140,150,160 };
	swprintf(wCh, 100, L"�1 ���= %d\0", MouseLBX1);
	DrawText(hdc, wCh, -1, &rect1, DT_LEFT);
	swprintf(wCh, 100, L"y1 ���= %d\0", MouseLBY1);
	DrawText(hdc, wCh, -1, &rect2, DT_LEFT);
	swprintf(wCh, 100, L"�2 ���= %d\0", MouseLBX2);
	DrawText(hdc, wCh, -1, &rect3, DT_LEFT);
	swprintf(wCh, 100, L"y2 ���= %d\0", MouseLBY2);
	DrawText(hdc, wCh, -1, &rect4, DT_LEFT);
	swprintf(wCh, 100, L"x1 ���= %d\0", MouseRBX1);
	DrawText(hdc, wCh, -1, &rect5, DT_LEFT);
	swprintf(wCh, 100, L"y1 ���= %d\0", MouseRBY1);
	DrawText(hdc, wCh, -1, &rect6, DT_LEFT);
	swprintf(wCh, 100, L"x2 ���= %d\0", MouseRBX2);
	DrawText(hdc, wCh, -1, &rect7, DT_LEFT);
	swprintf(wCh, 100, L"y2 ���= %d\0", MouseRBY2);
	DrawText(hdc, wCh, -1, &rect8, DT_LEFT);
//*/\ otladka
// ������ ����� ������ ����� ��� ������ � ����� ������������ �����
	if (!LBDisabled && LB_status == 2)
	{
		if (!SkipLBRect)
		{
			SelectObject(hdc, LBLinePen);
			SelectObject(hdc, GetStockObject(NULL_BRUSH));	// �������� ������ ���� �����
			result = Rectangle(hdc, MouseLBX1, MouseLBY1, MouseLBX2, MouseLBY2);
		}
		LB_status = 1;
	}
	// ������ ����� ������ ����� ��� ������ � ����� ������������ �����
	if (!RBDisabled && RB_status == 2)
	{
		if (!SkipRBRect)
		{
			SelectObject(hdc, RBLinePen);
			SelectObject(hdc, GetStockObject(NULL_BRUSH));	// �������� ������ ���� �����
			result = Rectangle(hdc, MouseRBX1, MouseRBY1, MouseRBX2, MouseRBY2);
		}
		RB_status = 1;
	}
};

void SelFrame::wm_mousemove(int mouseX, int mouseY)
{
	result = TrackMouseEvent(&tme);
	if (!LBDisabled && LB_status == 1)
	{
		LB_status = 2;	// ������ ��� - ������, ����� ���������� �����
		MouseLBX2 = mouseX;
		MouseLBY2 = mouseY;
		rect = {MouseLBX1, MouseLBY1, MouseLBX2, MouseLBY2}; // ������� ������ ��������� �������
		InvalidateRect(0, &rect, TRUE);
	}
	if (!RBDisabled && RB_status == 1)
	{
		RB_status = 2;	// ������ ��� - ������, ����� ���������� �����
		MouseRBX2 = mouseX;
		MouseRBY2 = mouseY;
		rect = { MouseRBX1, MouseRBY1, MouseRBX2, MouseRBY2 }; // ������� ������ ��������� �������
		InvalidateRect(0, &rect, TRUE);
	}
};

void SelFrame::wm_mouseleave()
{
	if (!LBDisabled && LB_status >= 1)
	{
		LB_status = 0;	// ��������� ������ "�� ������", ���� ���� ��� ������� �������
		rect = { MouseLBX1, MouseLBY1, MouseLBX2, MouseLBY2 };
		InvalidateRect(0, &rect, TRUE); // �������������� ������� ��-��� ����� �� ����� �� ������
//-\/ otladka �������������� ������� � ������� ��������� �������
		rect = { 4,0,150,160 };
		InvalidateRect(0, &rect, TRUE);
//-/\ otladka
	}
	if (!RBDisabled && RB_status >= 1)
	{
		RB_status = 0;	// ��������� ������ "�� ������", ���� ���� ��� ������� �������
		rect = { MouseRBX1, MouseRBY1, MouseRBX2, MouseRBY2 };
		InvalidateRect(0, &rect, TRUE); // �������������� ������� ��-��� ����� �� ����� �� ������
//-\/ otladka �������������� ������� � ������� ��������� �������
		rect = { 4,0,150,160 };
		InvalidateRect(0, &rect, TRUE);
//-/\ otladka
	}
};

void SelFrame::SetMode(signed char ObjectMode)
{
	MouseLBX1 = MouseLBY1 = 0;
	MouseLBX2 = MouseLBY2 = 0;
	MouseRBX1 = MouseRBY1 = 0;
	MouseRBX2 = MouseRBY2 = 0;
	switch (ObjectMode)
	{
		case -2:	// ���: ������ ��������
			LBDisabled = FALSE;
			SkipLBRect = TRUE;
			LB_status = 0;
			break;
		case -3:	// ���: �������� � ���������
			LBDisabled = FALSE;
			SkipLBRect = FALSE;
			LB_status = 0;
			break;
		case -4:	// ���: �� ��������
			LBDisabled = TRUE;
			LB_status = 0;
			break;
		case 2:	// ���: ������ ��������
			RBDisabled = FALSE;
			SkipRBRect = TRUE;
			RB_status = 0;
			break;
		case 3:	// ���: �������� � ���������
			RBDisabled = FALSE;
			SkipRBRect = FALSE;
			RB_status = 0;
			break;
		case 4:	// ���: �� ��������
			RBDisabled = TRUE;
			RB_status = 0;
			break;
	}
//-\/ otladka �������������� ������� � ������� ��������� �������
	rect = { 4,0,150,160 };
	InvalidateRect(0, &rect, TRUE);
//-/\ otladka
};
