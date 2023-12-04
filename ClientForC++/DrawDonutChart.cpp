#include"Gui.h"
#include<math.h>
#include<string>

void drawDonutChart(HDC hdc, HFONT hFontTitle, int left, int top, int right, int bottom, const int& mousture)
{
	const float coef = 3.6f;
	HBRUSH hPaintBrush = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(255, 255, 255));

	float gul = (((coef * mousture) * 3.14) / 180) + 3.14 / 2;

	float r = (right - left) / 2;
	float x0 = (left + right) / 2;
	float y0 = (top + bottom) / 2;
	float xrr2 = x0 + (r * cos(gul));
	float yrr2 = y0 - (r * sin(gul));

	SelectObject(hdc, hPaintBrush);
	Pie(hdc, left, top, right, bottom, x0, top, xrr2, yrr2);

	SelectObject(hdc, hBackgroundBrush);
	Ellipse(hdc, left + 20, top + 20, right - 20, bottom - 20);

	std::string str = std::to_string(mousture) + "%";
	SelectObject(hdc, hFontTitle);
	TextOutA(hdc, x0 - 10, y0 - 10, str.c_str(), str.size());

	DeleteObject(hPaintBrush);
	DeleteObject(hBackgroundBrush);
}