#pragma once
#include"Irrigation.h"
#include"SettingsManualIrrigation.h"
#include"SettingsAutoIrrigation.h"

class FirstSectionManual: public SettingManualIrrigation
{
public:
	void nextSection() override;
	void previousSection() override {}
};

class SecondSectionManual: public SettingManualIrrigation
{
public:

	void nextSection() override;
	void previousSection() override;
};


class ThirdSectionManual: public SettingManualIrrigation
{
public:
	void nextSection() override;
	void previousSection() override;
};

class FourthSectionManual: public SettingManualIrrigation
{
public:
	void nextSection() override;
	void previousSection() override;
};


class FifthSectionManual: public SettingManualIrrigation
{
public:
	void nextSection() override;
	void previousSection() override;
};

class SixthSectionManual: public SettingManualIrrigation
{
public:
	void nextSection() override {}
	void previousSection() override;
};



class FirstSectionAuto: public SettingAutoIrrigation
{
public:
	void nextSection() override;
	void previousSection() override {}
};

class SecondSectionAuto: public SettingAutoIrrigation
{
public:
	void nextSection() override;
	void previousSection() override;
};

class ThirdSectionAuto: public SettingAutoIrrigation
{
public:
	void nextSection() override;
	void previousSection() override;
};

class FourthSectionAuto: public SettingAutoIrrigation
{
public:
	void nextSection() override;
	void previousSection() override;
};


class FifthSectionAuto: public SettingAutoIrrigation
{
public:
	void nextSection() override;
	void previousSection() override;
};


class SixthSectionAuto: public SettingAutoIrrigation
{
public:
	void nextSection() override {}
	void previousSection() override;
};