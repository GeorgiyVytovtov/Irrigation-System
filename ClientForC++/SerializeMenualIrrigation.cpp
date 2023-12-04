#include"SerializeMenualSettings.h"

SerializeMenualSettings* SerializeMenualSettings::serializeMenual_ = nullptr;

SerializeMenualSettings* SerializeMenualSettings::getSerializ()
{
	if (serializeMenual_ == nullptr)
	{
		serializeMenual_ = new SerializeMenualSettings();
	}
	return serializeMenual_;
}

SerializeMenualSettings::SerializeMenualSettings() {
	settingsIrrigation = { new FirstSectionManual, new SecondSectionManual, new ThirdSectionManual, new FourthSectionManual, new FifthSectionManual, new SixthSectionManual };
	std::string data;
	std::fstream f(path_, std::fstream::in | std::fstream::app | std::ios::binary);
	f >> isSerializeSettings;
	f >> data;
	f.close();
	if (isSerializeSettings)
	{
		parse(data);
	}
}

SerializeMenualSettings::~SerializeMenualSettings()
{
	delete serializeMenual_;
}

void SerializeMenualSettings::parse(std::string data)
{
	std::vector<std::string> settings{ 5 };
	int n = 0, k = 0, i = 1;

	while (k < NUMBER_PLOTS)
	{
		if (data[i] == 'n')
		{
			i++;
			settings[n] = std::to_string(true);
		}
		else
		{
			settings[n] = std::to_string(data[i] - '0');
			i += 2;
			while (n < 4)
			{
				if (data[i] != ',' && data[i] != ')')
				{
					settings[n+1] = data.substr(i, 5);
					i += 5;
				}
				else {
					i += 1;
					n++;
				}
			}
		}
		settingsIrrigation[k]->setSavingData(settings);
		k++;
		n = 0;
		settings[0] = settings[1] = settings[2] = settings[3] = settings[4] = "";
	}
}

void SerializeMenualSettings::serializeAll()
{
	std::fstream f(path_, std::fstream::out | std::ios::binary);
	f << isSerializeSettings;
	f << '\n';
	f << getSettingsIrrigationText();
	f.close();
}