#pragma once
#include<vector>
#include"Irrigation.h"

class Irrigation;
class SettingsIrrigation
{
protected:
	Irrigation* irrigation = nullptr;
	bool isIrrigation = true;
public:
	void changeIsIrrigation()
	{
		isIrrigation = !isIrrigation;
	}
	virtual ~SettingsIrrigation(){}
	virtual void setSettingsIrrigation(Irrigation* irrigation) = 0;
	virtual void getData(HWND& hDlg) = 0;
	virtual void setData(HWND& hDlg, int numbPlace) = 0;
	virtual void isIrrigations(HWND& hDlg) = 0;
	virtual void nextSection() = 0;
	virtual void previousSection() = 0;
	virtual std::string getSavingData()const = 0;
	virtual void setSavingData(std::vector<std::string> data) = 0;
};