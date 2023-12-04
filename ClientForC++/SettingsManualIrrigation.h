#pragma once
#include"SettingsIrrigation.h"

class SettingManualIrrigation : public SettingsIrrigation
{
protected:
	std::string startTimeMorningIrrigation_;
	std::string startTimeEveningIrrigation_;
	std::string durationMorningIrrigation_;
	std::string durationEveningIrrigation_;
public:
	~SettingManualIrrigation() override{}
	void setSettingsIrrigation(Irrigation* irrigation)override;
	void getData(HWND& hDlg)override;
	void setData(HWND& hDlg, int numbPlace) override;
	void isIrrigations(HWND& hDlg)override;
	std::string getSavingData()const override;
	void setSavingData(std::vector<std::string> data) override;
};