#include"Irrigation.h"

Irrigation::Irrigation(SettingsIrrigation* settingIrrigation) :currentSettingIrrigation_(nullptr) {
	setSettingIrrigation(settingIrrigation);
}

Irrigation::~Irrigation()
{
	for (int i = 0; i < NUMBER_PLOTS; i++)
	{
		if (settingsIrrigation_[i] != nullptr)
			delete settingsIrrigation_[i];
	}
	delete currentSettingIrrigation_;
}

void Irrigation::saveCurrentSettingIrrigation(HWND& hDlg)
{
	currentSettingIrrigation_->getData(hDlg);
	std::swap(settingsIrrigation_[currentPlace_], currentSettingIrrigation_);
}

void Irrigation::setSettingsIrrigation(HWND& hDlg, std::array<SettingsIrrigation*, NUMBER_PLOTS>& settingsIrrigation)
{
	currentPlace_ = 0;
	std::swap(settingsIrrigation_, settingsIrrigation);
	for (auto& elem : settingsIrrigation_)
	{
		if (elem != nullptr)
			elem->setSettingsIrrigation(this);
	}
	currentSettingIrrigation_ = settingsIrrigation_[currentPlace_];
	currentSettingIrrigation_->setData(hDlg, currentPlace_);
}

std::array<SettingsIrrigation*, NUMBER_PLOTS>& Irrigation::getSettings()
{
	return settingsIrrigation_;
}

void Irrigation::nextSection(HWND& hDlg)
{
	if (currentPlace_ < NUMBER_PLOTS-1)
	{
		currentSettingIrrigation_->getData(hDlg);
		currentSettingIrrigation_->nextSection();
		currentPlace_++;
		if (settingsIrrigation_[currentPlace_] != nullptr) {
			std::swap(currentSettingIrrigation_, settingsIrrigation_[currentPlace_]);
		}
		currentSettingIrrigation_->setData(hDlg, currentPlace_);
	}
}

void Irrigation::previousSection(HWND& hDlg) {
	if (currentPlace_)
	{
		currentSettingIrrigation_->getData(hDlg);
		currentSettingIrrigation_->previousSection();
		currentPlace_--;
		if (settingsIrrigation_[currentPlace_] != nullptr) {
			std::swap(currentSettingIrrigation_, settingsIrrigation_[currentPlace_]);
		}
		currentSettingIrrigation_->setData(hDlg, currentPlace_);
	}
}

void Irrigation::isIrrigation(HWND& hDlg)
{
	currentSettingIrrigation_->changeIsIrrigation();
	currentSettingIrrigation_->isIrrigations(hDlg);
}


void Irrigation::setSettingIrrigation(SettingsIrrigation* settingIrrigation)
{
	if (currentSettingIrrigation_ != nullptr) {
		std::swap(settingsIrrigation_[currentPlace_], currentSettingIrrigation_);
	}
	currentSettingIrrigation_ = settingIrrigation;
	currentSettingIrrigation_->setSettingsIrrigation(this);
}
