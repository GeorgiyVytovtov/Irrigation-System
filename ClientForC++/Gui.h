#pragma once
#include<string>
#include<Windows.h>


INT_PTR CALLBACK ConnectionSettingsDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK ManualSettingsDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK AutoSettingsDialog(HWND, UINT, WPARAM, LPARAM);
void drawDonutChart(HDC hdc, HFONT hFontTitle, int left, int top, int right, int bottom, const int& mousture);
