#include"Irrigation.h"
#include"IrrigationPlots.h"

void SettingAutoIrrigation::setSettingsIrrigation(Irrigation* irrigation) {
	this->irrigation = irrigation;
}

void SettingAutoIrrigation::getData(HWND& hDlg)
{
	this->isIrrigation = IsDlgButtonChecked(hDlg, IDC_IS_IRRIGATION);
	this->maxSoilMoisture_ = GetDlgItemInt(hDlg, IDC_EDIT_MAX, 0, 0);
	this->minSoilMoisture_ = GetDlgItemInt(hDlg, IDC_EDIT_MIN, 0, 0);
}

void SettingAutoIrrigation::setData(HWND& hDlg, int numbPlace)
{
	SendDlgItemMessage(hDlg, IDC_IS_IRRIGATION, BM_SETCHECK, isIrrigation, 0);
	SetDlgItemTextA(hDlg, IDC_EDIT_MAX, std::to_string(maxSoilMoisture_).c_str());
	SetDlgItemTextA(hDlg, IDC_EDIT_MIN, std::to_string(minSoilMoisture_).c_str());
	SetDlgItemTextA(hDlg, IDC_CURRENT_PLACE, std::to_string(numbPlace + 1).append(" Plots").c_str());
	isIrrigations(hDlg);
}

void SettingAutoIrrigation::isIrrigations(HWND& hDlg)
{
	EnableWindow(GetDlgItem(hDlg, IDC_EDIT_MIN), isIrrigation);
	EnableWindow(GetDlgItem(hDlg, IDC_EDIT_MAX), isIrrigation);
	EnableWindow(GetDlgItem(hDlg, IDC_SPIN_MAX), isIrrigation);
	EnableWindow(GetDlgItem(hDlg, IDC_SPIN_MIN),isIrrigation);
}

void SettingAutoIrrigation::setSavingData(std::vector<std::string> data) {
	this->isIrrigation = atoi(data[0].c_str());
	this->maxSoilMoisture_ = atoi(data[1].c_str());
	this->minSoilMoisture_ = atoi(data[2].c_str());
}

std::string SettingAutoIrrigation::getSavingData()const
{
	return std::to_string(isIrrigation) + "(" + std::to_string(maxSoilMoisture_) + ";" + std::to_string(minSoilMoisture_) + ")";
}

void FirstSectionAuto::nextSection() {
	irrigation->setSettingIrrigation(new SecondSectionAuto());
}

void SecondSectionAuto::previousSection()  {
	irrigation->setSettingIrrigation(new FirstSectionAuto());
}

void SecondSectionAuto::nextSection() {
	irrigation->setSettingIrrigation(new ThirdSectionAuto());
}

void ThirdSectionAuto::previousSection()  {
	irrigation->setSettingIrrigation(new SecondSectionAuto());
}

void FourthSectionAuto::previousSection()  {
	irrigation->setSettingIrrigation(new ThirdSectionAuto());
}

void ThirdSectionAuto::nextSection() {
	irrigation->setSettingIrrigation(new FourthSectionAuto());
}

void FifthSectionAuto::previousSection()  {
	irrigation->setSettingIrrigation(new FourthSectionAuto());
}

void FourthSectionAuto::nextSection() {
	irrigation->setSettingIrrigation(new FifthSectionAuto());
}

void FifthSectionAuto::nextSection() {
	irrigation->setSettingIrrigation(new SixthSectionAuto());
}

void SixthSectionAuto::previousSection() {
	irrigation->setSettingIrrigation(new FifthSectionAuto());
}