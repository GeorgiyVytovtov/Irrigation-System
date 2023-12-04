#include"Irrigation.h"
#include"IrrigationPlots.h"

void SettingManualIrrigation::setSettingsIrrigation(Irrigation* irrigation) {
	this->irrigation = irrigation;
}

void SettingManualIrrigation::getData(HWND& hDlg)
{
	char buff[6];
	this->isIrrigation = IsDlgButtonChecked(hDlg, IDC_IS_IRRIGATION);
	GetDlgItemTextA(hDlg, IDC_TIME_MORNING_IRRIGATION, buff, 6);
	startTimeMorningIrrigation_ = buff;
	if (startTimeMorningIrrigation_.size() != 5)
		startTimeMorningIrrigation_.clear();
	GetDlgItemTextA(hDlg, IDC_DURATION_MORNING_IRRIGATION, buff, 6);
	durationMorningIrrigation_ = buff;
	if (durationMorningIrrigation_.size() != 5)
		durationMorningIrrigation_.clear();
	GetDlgItemTextA(hDlg, IDC_TIME_EVENING_IRRIGATION, buff, 6);
	startTimeEveningIrrigation_ = buff;
	if (startTimeEveningIrrigation_.size() != 5)
		startTimeEveningIrrigation_.clear();
	GetDlgItemTextA(hDlg, IDC_DURATION_EVENING_IRRIGATION, buff, 6);
	durationEveningIrrigation_ = buff;
	if (durationEveningIrrigation_.size() != 5)
		durationEveningIrrigation_.clear();
}

void SettingManualIrrigation::setData(HWND& hDlg, int numbPlace)
{
	SetDlgItemTextA(hDlg, IDC_CURRENT_PLACE, std::to_string(numbPlace + 1).append(" Plots").c_str());
	SendDlgItemMessage(hDlg, IDC_IS_IRRIGATION, BM_SETCHECK, isIrrigation, 0);
	SetDlgItemTextA(hDlg, IDC_TIME_MORNING_IRRIGATION, startTimeMorningIrrigation_.c_str());
	SetDlgItemTextA(hDlg, IDC_DURATION_MORNING_IRRIGATION, durationMorningIrrigation_.c_str());
	SetDlgItemTextA(hDlg, IDC_TIME_EVENING_IRRIGATION, startTimeEveningIrrigation_.c_str());
	SetDlgItemTextA(hDlg, IDC_DURATION_EVENING_IRRIGATION, durationEveningIrrigation_.c_str());
	isIrrigations(hDlg);
}

void SettingManualIrrigation::isIrrigations(HWND& hDlg)
{
	EnableWindow(GetDlgItem(hDlg, IDC_TIME_MORNING_IRRIGATION), isIrrigation);
	EnableWindow(GetDlgItem(hDlg, IDC_DURATION_MORNING_IRRIGATION), isIrrigation);
	EnableWindow(GetDlgItem(hDlg, IDC_TIME_EVENING_IRRIGATION), isIrrigation);
	EnableWindow(GetDlgItem(hDlg, IDC_DURATION_EVENING_IRRIGATION), isIrrigation);
}

void SettingManualIrrigation::setSavingData(std::vector<std::string> data) {
	this->isIrrigation = atoi(data[0].c_str());
	this->startTimeMorningIrrigation_ = data[1];
	this->durationMorningIrrigation_ = data[2];
	this->startTimeEveningIrrigation_ = data[3];
	this->durationEveningIrrigation_ = data[4];
}

std::string SettingManualIrrigation::getSavingData()const
{
	return std::to_string(isIrrigation) + "(" + startTimeMorningIrrigation_ + "," + durationMorningIrrigation_ + "," + startTimeEveningIrrigation_ + "," + durationEveningIrrigation_ + ")";
}


void FirstSectionManual::nextSection() {
	irrigation->setSettingIrrigation(new SecondSectionManual());
}

void SecondSectionManual::nextSection() {
	irrigation->setSettingIrrigation(new ThirdSectionManual());
}

void SecondSectionManual::previousSection() {
	irrigation->setSettingIrrigation(new FirstSectionManual());
}

void ThirdSectionManual::nextSection() {
	irrigation->setSettingIrrigation(new FourthSectionManual());
}

void ThirdSectionManual::previousSection() {
	irrigation->setSettingIrrigation(new SecondSectionManual());
}

void FourthSectionManual::nextSection() {
	irrigation->setSettingIrrigation(new FifthSectionManual());
}

void FourthSectionManual::previousSection() {
	irrigation->setSettingIrrigation(new ThirdSectionManual());
}

void FifthSectionManual::previousSection() {
	irrigation->setSettingIrrigation(new FourthSectionManual());
}

void FifthSectionManual::nextSection() {
	irrigation->setSettingIrrigation(new SixthSectionManual());
}

void SixthSectionManual::previousSection() {
	irrigation->setSettingIrrigation(new FifthSectionManual());
}