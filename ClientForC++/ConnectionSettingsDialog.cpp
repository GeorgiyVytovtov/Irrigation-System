#include<WinSock2.h>
#include"Network.h"
#include"Gui.h"
#include"resource.h"
#include<wingdi.h>
#include<tchar.h>
#include<commctrl.h>


static Network* network;

INT_PTR CALLBACK ConnectionSettingsDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		network = (Network*)lParam;
		SetDlgItemTextA(hDlg, IDC_IP_ADDRESS, network->getIpAddress().c_str());
		if(network->getPort())
			SetDlgItemInt(hDlg, IDC_PORT, network->getPort(),0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			return EndDialog(hDlg, 0);
			break;
		case IDOK:
			std::string ipAddress;
			char buff[15];
			
			GetDlgItemTextA(hDlg, IDC_IP_ADDRESS, buff, 14);
			ipAddress += buff;
			network->setIpAddress(ipAddress);
			GetDlgItemTextA(hDlg, IDC_PORT, buff, 14);
			network->setPort(atoi(buff));
			return EndDialog(hDlg, 1);
			break;
		}
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}