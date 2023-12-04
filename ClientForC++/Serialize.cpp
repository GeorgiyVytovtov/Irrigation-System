#include"Serialize.h"
#include"SettingsIrrigation.h"


Serialize::~Serialize()
{
	for (int i = 0; i < NUMBER_PLOTS; i++)
	{
		if (settingsIrrigation[i] != nullptr)
			delete settingsIrrigation[i];
	}
}

bool Serialize::getIsSerializeSettings()const {
	return isSerializeSettings;
}

void Serialize::serializeSettingsIrrigation(std::array<SettingsIrrigation*, NUMBER_PLOTS>& settingsIrrigation)
{
	std::swap(this->settingsIrrigation, settingsIrrigation);
	isSerializeSettings = true;
}

std::array<SettingsIrrigation*, NUMBER_PLOTS>& Serialize::getSettingsIrrigation()
{
	return settingsIrrigation;
}

std::string Serialize::getSettingsIrrigationText()
{
	std::string setting = "{";
	for (const auto& elem : settingsIrrigation)
	{
		if (elem != nullptr)
			setting += elem->getSavingData();
		else
			setting += "n"; 
	}
	setting += "}";
	return setting;
}