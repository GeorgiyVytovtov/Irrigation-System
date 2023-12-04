#pragma once
#include<utility>
#include<fstream>
#include"Irrigation.h"
#include"IrrigationPlots.h"


class Serialize
{
protected:
	std::array<SettingsIrrigation*, NUMBER_PLOTS> settingsIrrigation;
	bool isSerializeSettings = false;
public:
	void serializeSettingsIrrigation(std::array<SettingsIrrigation*, NUMBER_PLOTS>& settingsIrrigation);
	std::array<SettingsIrrigation*, NUMBER_PLOTS>& getSettingsIrrigation();
	std::string getSettingsIrrigationText();
	bool getIsSerializeSettings()const;
	virtual void serializeAll() = 0;
	virtual ~Serialize();
};
