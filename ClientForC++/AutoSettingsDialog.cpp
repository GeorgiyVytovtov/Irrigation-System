#include"Gui.h"
#include"Irrigation.h"
#include"IrrigationPlots.h"
#include"resource.h"
#include"Serialize.h"
#include"SerializeAutoSettings.h"
#include<memory>
#include<wingdi.h>
#include<tchar.h>
#include<commctrl.h>


static Irrigation* autoIrrigation;
INT_PTR CALLBACK AutoSettingsDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hSpinMax, hBuddyMax, hSpinMin, hBuddyMin;

	switch (message)
	{
	case WM_INITDIALOG:

		if(autoIrrigation==nullptr)
			autoIrrigation = new Irrigation(new FirstSectionAuto());

		SendDlgItemMessage(hDlg, IDC_IS_IRRIGATION, BM_SETCHECK, 1, 0);
		SetDlgItemText(hDlg, IDC_EDIT_MIN, _T("0"));
		SetDlgItemText(hDlg, IDC_EDIT_MAX, _T("0"));

		hSpinMax = GetDlgItem(hDlg, IDC_SPIN_MAX);
		hBuddyMax = GetDlgItem(hDlg, IDC_EDIT_MAX);
		SendMessage(hSpinMax, UDM_SETBUDDY, (WPARAM)hBuddyMax, 0);
		SendDlgItemMessage(hDlg, IDC_SPIN_MAX, UDM_SETRANGE, 0, 100);

		hSpinMin = GetDlgItem(hDlg, IDC_SPIN_MIN);
		hBuddyMin = GetDlgItem(hDlg, IDC_EDIT_MIN);
		SendMessage(hSpinMin, UDM_SETBUDDY, (WPARAM)hBuddyMin, 0);
		SendDlgItemMessage(hDlg, IDC_SPIN_MIN, UDM_SETRANGE, 0, 100);
		
		
		if (SerializeAutoSettings::getSerializ()->getIsSerializeSettings())
			autoIrrigation->setSettingsIrrigation(hDlg, SerializeAutoSettings::getSerializ()->getSettingsIrrigation());

		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_PRIVIOUS:
			autoIrrigation->previousSection(hDlg);
			break;
		case IDC_NEXT:
			autoIrrigation->nextSection(hDlg);
			break;
		case IDC_IS_IRRIGATION:
			autoIrrigation->isIrrigation(hDlg);
			break;
		case IDCANCEL:
			if (!SerializeAutoSettings::getSerializ()->getIsSerializeSettings()) {
				delete autoIrrigation;
				autoIrrigation = nullptr;
				EndDialog(hDlg, 0);
			}
			else {
				autoIrrigation->saveCurrentSettingIrrigation(hDlg);
				SerializeAutoSettings::getSerializ()->serializeSettingsIrrigation(autoIrrigation->getSettings());
				EndDialog(hDlg, 1);
			}
			break;
		case IDC_SAVING:
			autoIrrigation->saveCurrentSettingIrrigation(hDlg);
			SerializeAutoSettings::getSerializ()->serializeSettingsIrrigation(autoIrrigation->getSettings());
			return EndDialog(hDlg, 1);
			break;
		}
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}