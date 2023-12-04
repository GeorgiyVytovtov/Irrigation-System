#include<WinSock2.h>
#include<Windows.h>
#include<string>
#include<tchar.h>
#include<memory>
#include<commdlg.h>
#include<commctrl.h>

#include"Network.h"
#include"Gui.h"
#include"SerializeMenualSettings.h"
#include"SerializeAutoSettings.h"
#include"InfoAboutIrrigation.h"
#include"Settings.h"
#include"resource.h"
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma warning(disable: 4996)

static HWND hStart, hStop, hUpdata, hInfAboutIrrigation;

HINSTANCE hInst;

HFONT hFontTitle = CreateFont(18, 0, 0, 0, FW_EXTRALIGHT, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FF_MODERN, _T("Times New Roman"));

std::unique_ptr<InfoAboutIrrigation> infAboutIrrigation;
std::unique_ptr<Network> network{ std::make_unique<Network>() };
static Settings st;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	RECT rt;
	HDC hdc;

	switch (msg)
	{
	case WM_CREATE: 
	{	
		hStart = CreateWindow(
			WC_BUTTON,
			_T("Start"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			170, 250, 100, 30,
			hWnd, reinterpret_cast<HMENU>(START), NULL, NULL);

		hStop = CreateWindow(
			WC_BUTTON,
			_T("Stop"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			30, 250, 100, 30,
			hWnd, reinterpret_cast<HMENU>(STOP), NULL, NULL);

		hUpdata = CreateWindow(
			WC_BUTTON,
			NULL,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON|BS_BITMAP,
			280, 250, 30, 30,
			hWnd, reinterpret_cast<HMENU>(UPDATA), NULL, NULL);

		HWND AutoRadioButton = CreateWindow(
			WC_BUTTON,
			_T("Auto"),
			WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
			40,220,80,20,
			hWnd, reinterpret_cast<HMENU>(AUTO), NULL, NULL);

		HWND ManualRadioButton = CreateWindow(
			WC_BUTTON,
			_T("Manual"),
			WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
			180, 220, 80, 20,
			hWnd, reinterpret_cast<HMENU>(MANUAL), NULL, NULL);

		HWND DataGroupBox = CreateWindow(
			WC_BUTTON,
			_T("Data with Sensors"),
			WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
			20, 300, 690, 430,
			hWnd, NULL, NULL, NULL);

		HWND hGroupBox = CreateWindow(
			WC_BUTTON,
			NULL,
			WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
			20, 200, 300, 90,
			hWnd, NULL, NULL, NULL);

		HWND InfoGroupBox = CreateWindow(
			WC_BUTTON,
			_T("Information about irrigation different plants"),
			WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
			340, 10, 370, 280,
			hWnd, NULL, NULL, NULL);

		hInfAboutIrrigation = CreateWindow(
			WC_EDIT,
			NULL,
			WS_CHILD | WS_VISIBLE |WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_READONLY,
			350, 180, 350, 100,
			hWnd, NULL, NULL, NULL);

		HWND hPrevious = CreateWindow(
			WC_BUTTON,
			_T("<<"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			350, 100, 30, 30,
			hWnd, reinterpret_cast<HMENU>(PREVIOUS), NULL, NULL);

		HWND hNext = CreateWindow(
			WC_BUTTON,
			_T(">>"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			670, 100, 30, 30,
			hWnd, reinterpret_cast<HMENU>(NEXT), NULL, NULL);


		SendMessage(hStart, WM_SETFONT, (WPARAM)hFontTitle, true);
		SendMessage(hStop, WM_SETFONT, (WPARAM)hFontTitle, true);
		SendMessage(hUpdata, WM_SETFONT, (WPARAM)hFontTitle, true);
		SendMessage(hNext, WM_SETFONT, (WPARAM)hFontTitle, true);
		SendMessage(hPrevious, WM_SETFONT, (WPARAM)hFontTitle, true);
		SendMessage(AutoRadioButton, WM_SETFONT, (WPARAM)hFontTitle, true);
		SendMessage(ManualRadioButton, WM_SETFONT, (WPARAM)hFontTitle, true);
		SendMessage(DataGroupBox, WM_SETFONT, (WPARAM)hFontTitle, true);
		SendMessage(InfoGroupBox, WM_SETFONT, (WPARAM)hFontTitle, true);
		SendMessage(hInfAboutIrrigation, WM_SETFONT, (WPARAM)hFontTitle, true);

		HBITMAP updataImage = (HBITMAP)LoadImageA(NULL, "img_updata.bmp", IMAGE_BITMAP, 28, 28, LR_LOADFROMFILE);
		SendMessage(hUpdata, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)updataImage);

		EnableWindow(hStart, !st.isStarted);
		EnableWindow(hStop, st.isStarted);
		EnableWindow(hUpdata, st.isUpdata);
		SendDlgItemMessage(hWnd, AUTO, BM_SETCHECK, st.isAuto, 0);
		SendDlgItemMessage(hWnd, MANUAL, BM_SETCHECK, st.isManual, 0);

		infAboutIrrigation = { std::make_unique<InfoAboutIrrigation>(hInfAboutIrrigation) };

		if (st.isSettingsConnection)
		{
			network->setIpAddress(st.ipAddress);
			network->setPort(st.port);
		}

		if (st.isStarted && !network->start(hWnd))
			MessageBoxA(hWnd, "Error connection. After starting the program, click STOP button, and then try to start the system again by clicking START button or restart the application again later.", "Error connection", MB_OK|MB_ICONERROR);

	}
	break;

	case WM_COMMAND: 
	{
		switch (LOWORD(wParam))
		{

		case ID_AUTO_SETTINGS:
		{
			st.isSettingsAuto = DialogBox(hInst, MAKEINTRESOURCE(IDD_SETTINGS_AUTO_IRRIGATION), hWnd, AutoSettingsDialog);
			if (st.isAuto) {
				st.isUpdata = true;
				EnableWindow(hUpdata, st.isUpdata);
			}
		}
		break;

		case ID_MANUAL_SETTINGS:
		{
			st.isSettingsManual = DialogBox(hInst, MAKEINTRESOURCE(IDD_SETTINGS_MANUAL_IRRIGATION), hWnd, ManualSettingsDialog);
			if (st.isManual) {
				st.isUpdata = true;
				EnableWindow(hUpdata, st.isUpdata);
			}
		}
		break;
		
		case ID_SETTINGS_CONNECTION:
		{
			bool isSettingsConnection = DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_SETTINGS_CONNECTION), hWnd, ConnectionSettingsDialog, (LPARAM)network.get());
			if (isSettingsConnection)
				st.isSettingsConnection = isSettingsConnection;
		}
		break;

		case ID_EXIT:
		{
			SendMessage(hWnd, WM_DESTROY, 0, 0);
		}
		break;

		case ID_ABOUT:
		{
			MessageBoxA(hWnd, "This program is designed to control soil moisture when growing plants at home, in the garden or in a greenhouse. The program provides two modes for setting soil moisture control, automatic for upper and lower humidity values and manual for self-adjusting morning and evening watering time intervals", "About program", MB_ICONINFORMATION | MB_OK);
		}
		break;
		
		case AUTO:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (SendDlgItemMessage(hWnd, AUTO, BM_GETCHECK, 0, 0) == 0)
				{
					if (st.isSettingsAuto)
					{
						SendDlgItemMessage(hWnd, AUTO, BM_SETCHECK, 1, 0);
						SendDlgItemMessage(hWnd, MANUAL, BM_SETCHECK, 0, 0);
						st.isAuto = !st.isAuto;
						st.isManual = false;
						st.isUpdata = true;
						EnableWindow(hUpdata, st.isUpdata);
					}
					else
						MessageBoxA(hWnd, "Please make settings in auto irrigation mode", "Warning: no settings in auto mode", MB_OK | MB_ICONWARNING);
				}
				break;
			}
		}
		break;

		case MANUAL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (SendDlgItemMessage(hWnd, MANUAL, BM_GETCHECK, 0, 0) == 0)
				{
					if (st.isSettingsManual)
					{
						SendDlgItemMessage(hWnd, MANUAL, BM_SETCHECK, 1, 0);
						SendDlgItemMessage(hWnd, AUTO, BM_SETCHECK, 0, 0);
						st.isManual = !st.isManual;
						st.isAuto = false;
						st.isUpdata = true;
						EnableWindow(hUpdata, st.isUpdata);
					}
					else
						MessageBoxA(hWnd, "Please make settings in manual irrigation mode", "Warning: no settings in manual mode", MB_OK | MB_ICONWARNING);
				}
				break;
			}
		}
		break;

		case START:
		{
			std::string command;
			if (!st.isAuto && !st.isManual) {
				MessageBoxA(hWnd, "Please choose mode irrigation", "Not selected mode irrigation", MB_OKCANCEL);
				break;
			}
			else if (st.isAuto) {
				command += "A" + SerializeAutoSettings::getSerializ()->getSettingsIrrigationText();
			}
			else if(st.isManual) {
				command += "M" + SerializeMenualSettings::getSerializ()->getSettingsIrrigationText();;
			}
			if (network->start(hWnd)) {
				network->sendData(command);
				EnableWindow(hStart, st.isStarted);
				EnableWindow(hStop, !st.isStarted);
				st.isUpdata = false;
				EnableWindow(hUpdata, st.isUpdata);
				st.isStarted = !st.isStarted;
			}
			else {
				MessageBoxA(hWnd, "Error connection, check corrected entered settings connection", "Error connection", MB_OK | MB_ICONERROR);
			}
		}
		break;

		case STOP:
		{
			EnableWindow(hStart, st.isStarted);
			EnableWindow(hStop, !st.isStarted);
			st.isStarted = !st.isStarted;
			network->stop();
		}
		break;

		case UPDATA:
		{
			if (!st.isStarted) {
				MessageBoxA(hWnd, "Please start the system", "Not started system", MB_OK | MB_ICONWARNING);
				break;
			}
			else if (st.isAuto)
			{
				network->sendData("A" + SerializeAutoSettings::getSerializ()->getSettingsIrrigationText());
			}
			else if (st.isManual)
			{
				network->sendData("M" + SerializeMenualSettings::getSerializ()->getSettingsIrrigationText());
			}
			st.isUpdata = false;
			EnableWindow(hUpdata, st.isUpdata);
		}
		break;

		case NEXT:
		{
			infAboutIrrigation->next(hInfAboutIrrigation);
		}
		break;

		case PREVIOUS:
		{
			infAboutIrrigation->previous(hInfAboutIrrigation);
		}
		break;

		default:
			break;
		}
	}
	break;

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		HBITMAP hBmp = (HBITMAP)LoadImageA(NULL, "img_greenhouse.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		HDC bmpDC = CreateCompatibleDC(hdc);
		SelectObject(bmpDC, hBmp);
		BitBlt(hdc, 20, 20, 800, 600, bmpDC, 0, 0, SRCCOPY);
		DeleteDC(bmpDC);
		DeleteObject(hBmp);

		                
		bmpDC = CreateCompatibleDC(hdc);
		SelectObject(bmpDC, infAboutIrrigation->getPhoto());
		BitBlt(hdc, 420, 35, 250, 200, bmpDC, 0, 0, SRCCOPY);       
		DeleteDC(bmpDC);

		int k = 0;
		std::vector<int> data = network->getData();
		for (int top = 330, bottom = 480; top <= 530; top += 200, bottom += 200)
		{
			for (int right = 250, left = 100; right <= 650; right += 200, left += 200)
			{
				drawDonutChart(hdc, hFontTitle, left, top, right, bottom, data[k]);
				k++;
			}
		}

		k = 0;
		for (int y = 490; y < 890; y += 200)
		{
			for (int x = 100; x < 700; x += 200)
			{
				std::string text = "Soil moisture in " + std::to_string(k+1) + " plot";
				SetRect(&rt, x, y, x+150, y+150);
				DrawTextA(hdc, text.c_str(), text.length(), &rt, DT_CENTER);
				k++;
			}
		}

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY: 
	{
		SerializeMenualSettings::getSerializ()->serializeAll();
		SerializeAutoSettings::getSerializ()->serializeAll();

		st.ipAddress = network->getIpAddress();
		st.port = network->getPort();

		network->sendData("exit");
		PostQuitMessage(0);
	}
	break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCEW(IDI_ICON1));
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCEW(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hInstance = hInstance;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU1);
	wc.lpszClassName = _T("WinMainClass");


	RegisterClassEx(&wc);
	hWnd = CreateWindow(
		wc.lpszClassName,
		_T("Irrigation"),
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		(GetSystemMetrics(SM_CXSCREEN) - 745) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - 805) / 2,
		745, 805,
		NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}