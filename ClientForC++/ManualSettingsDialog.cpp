#include"Gui.h"
#include"Irrigation.h"
#include"IrrigationPlots.h"
#include"resource.h"
#include"Serialize.h"
#include"SerializeMenualSettings.h"
#include<memory>
#include<wingdi.h>
#include<tchar.h>
#include<commctrl.h>


HINSTANCE hInstance;
WNDPROC DefEditProc;

LRESULT CALLBACK NewEditProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CHAR:
		char buff[6];
		GetWindowTextA(hwnd, buff, 6);
		std::string data = buff;

		if (!data.empty()) {
			if (data.size() != 2 && wParam == 58)
				return 0;
			if (data.size() == 2 && wParam != 8 && wParam != 58){
				return(0);
			}
			else
			{
				switch (data[data.size() - 1])
				{
				case '0':
					if (wParam != 8 &&(wParam <= 47 || wParam >= 59)) {
						return(0);
					}
					break;
				case '1':
					if (wParam != 8 &&(wParam <= 47 || wParam >= 59)) {
						return(0);
					}
					break;
				case '2':
					if (data.size() != 4 && wParam != 8 && (wParam <= 47 || wParam >= 53) && wParam != 58) {
						return(0);
					}
					else if (data.size() == 4 && wParam != 8 && (wParam <= 47 || wParam >= 59) && wParam != 58) {
						return 0;
					}
					break;
				case ':':
					if (wParam != 8 &&(wParam <= 47 || wParam >= 54)) {
							return(0);
					}
					break;
				default:
					break;
				}
			}
		}
		else {
			if (wParam != 8 && (wParam <= 47 || wParam >= 51)) {
				return(0);
			}
		}
	}
	return((LRESULT)CallWindowProc((WNDPROC)DefEditProc, hwnd, message, wParam, lParam));
}


static Irrigation* manualIrrigation;
INT_PTR CALLBACK ManualSettingsDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG:
		if (manualIrrigation == nullptr)
			manualIrrigation = new Irrigation(new FirstSectionManual());

		DefEditProc = (WNDPROC)GetWindowLongPtr(GetDlgItem(hDlg, IDC_TIME_MORNING_IRRIGATION), GWLP_WNDPROC);
		SetWindowLongPtr(GetDlgItem(hDlg, IDC_TIME_MORNING_IRRIGATION), GWLP_WNDPROC, (LPARAM)NewEditProc);
		DefEditProc = (WNDPROC)GetWindowLongPtr(GetDlgItem(hDlg, IDC_DURATION_MORNING_IRRIGATION), GWLP_WNDPROC);
		SetWindowLongPtr(GetDlgItem(hDlg, IDC_DURATION_MORNING_IRRIGATION), GWLP_WNDPROC, (LPARAM)NewEditProc);
		DefEditProc = (WNDPROC)GetWindowLongPtr(GetDlgItem(hDlg, IDC_TIME_EVENING_IRRIGATION), GWLP_WNDPROC);
		SetWindowLongPtr(GetDlgItem(hDlg, IDC_TIME_EVENING_IRRIGATION), GWLP_WNDPROC, (LPARAM)NewEditProc);
		DefEditProc = (WNDPROC)GetWindowLongPtr(GetDlgItem(hDlg, IDC_DURATION_EVENING_IRRIGATION), GWLP_WNDPROC);
		SetWindowLongPtr(GetDlgItem(hDlg, IDC_DURATION_EVENING_IRRIGATION), GWLP_WNDPROC, (LPARAM)NewEditProc);


		SendDlgItemMessage(hDlg, IDC_IS_IRRIGATION, BM_SETCHECK, 1, 0);
		SendDlgItemMessage(hDlg, IDC_TIME_MORNING_IRRIGATION, EM_SETLIMITTEXT, 5, 0);
		SendDlgItemMessage(hDlg, IDC_DURATION_MORNING_IRRIGATION, EM_SETLIMITTEXT, 5, 0);
		SendDlgItemMessage(hDlg, IDC_TIME_EVENING_IRRIGATION, EM_SETLIMITTEXT, 5, 0);
		SendDlgItemMessage(hDlg, IDC_DURATION_EVENING_IRRIGATION, EM_SETLIMITTEXT, 5, 0);

		
		
		if (SerializeMenualSettings::getSerializ()->getIsSerializeSettings())
			manualIrrigation->setSettingsIrrigation(hDlg, SerializeMenualSettings::getSerializ()->getSettingsIrrigation());

		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_NEXT:
			manualIrrigation->nextSection(hDlg);
			break;
		case IDC_PRIVIOUS:
			manualIrrigation->previousSection(hDlg);
			break;
		case IDC_IS_IRRIGATION:
			manualIrrigation->isIrrigation(hDlg);
			break;
		case IDCANCEL:
			if (!SerializeMenualSettings::getSerializ()->getIsSerializeSettings()) {
				delete manualIrrigation;
				manualIrrigation = nullptr;
				EndDialog(hDlg, 0);
			}
			else {
				manualIrrigation->saveCurrentSettingIrrigation(hDlg);
				SerializeMenualSettings::getSerializ()->serializeSettingsIrrigation(manualIrrigation->getSettings());
				EndDialog(hDlg, 1);
			}
			break;
		case IDC_SAVING:
			manualIrrigation->saveCurrentSettingIrrigation(hDlg);
			SerializeMenualSettings::getSerializ()->serializeSettingsIrrigation(manualIrrigation->getSettings());
			EndDialog(hDlg, 1);
			break;
		}
		return TRUE;
	default: 
		return FALSE;
	}
	return FALSE;
}