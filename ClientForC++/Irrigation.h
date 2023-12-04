#pragma once
#include<Windows.h>
#include<tchar.h>
#include<string>
#include<array>
#include<algorithm>
#include"resource.h"
#include"SettingsIrrigation.h"
#include"IrrigationPlots.h"
const size_t NUMBER_PLOTS = 6;

class Irrigation
{
private:
	unsigned int currentPlace_ = 0;
	std::array<SettingsIrrigation*, NUMBER_PLOTS> settingsIrrigation_;
	SettingsIrrigation* currentSettingIrrigation_;
public:
	Irrigation(SettingsIrrigation* settingIrrigation);
	~Irrigation();
	std::array<SettingsIrrigation*, NUMBER_PLOTS>& getSettings();
	void setSettingsIrrigation(HWND& hDlg, std::array<SettingsIrrigation*, NUMBER_PLOTS>& settingsIrrigation);
	void setSettingIrrigation(SettingsIrrigation* settingIrrigation);
	void nextSection(HWND& hDlg);
	void previousSection(HWND& hDlg);
	void saveCurrentSettingIrrigation(HWND& hDlg);
	void isIrrigation(HWND& hDlg);
};