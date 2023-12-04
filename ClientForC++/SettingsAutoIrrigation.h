#pragma once
#include"SettingsIrrigation.h"

class SettingAutoIrrigation : public SettingsIrrigation 
{
protected:
	int maxSoilMoisture_;
	int minSoilMoisture_;
public:
	~SettingAutoIrrigation() override {}
	void setSettingsIrrigation(Irrigation* irrigation)override;
	void getData(HWND& hDlg)override;
	void setData(HWND& hDlg, int numbPlace)override;
	void isIrrigations(HWND& hDlg)override;
	std::string getSavingData()const override;
	void setSavingData(std::vector<std::string> data) override;
};