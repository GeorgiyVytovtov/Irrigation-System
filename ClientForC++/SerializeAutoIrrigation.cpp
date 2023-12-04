#include"SerializeAutoSettings.h"

SerializeAutoSettings* SerializeAutoSettings::serializeAuto_ = nullptr;

SerializeAutoSettings* SerializeAutoSettings::getSerializ()
{
	if (serializeAuto_ == nullptr)
	{
		serializeAuto_ = new SerializeAutoSettings();
	}
	return serializeAuto_;
}

SerializeAutoSettings::SerializeAutoSettings() {
	settingsIrrigation = { new FirstSectionAuto, new SecondSectionAuto, new ThirdSectionAuto, new FourthSectionAuto, new FifthSectionAuto, new SixthSectionAuto };
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

SerializeAutoSettings::~SerializeAutoSettings()
{
	delete serializeAuto_;
}

void SerializeAutoSettings::parse(std::string data)
{
	std::vector<std::string> settings{3};
	int k = 0, n = 0, i = 1;

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
			std::string str = "";
			while (n < 2)
			{
				if (data[i] != ';' && data[i] != ')')
				{
					str += data[i];
				}
				else {
					settings[n+1]=str;
					str.clear();
					n++;
				}
				i++;
			}
		}
		settingsIrrigation[k]->setSavingData(settings);
		k++;
		n = 0;
		settings[0] = settings[1] = settings[2] = "";
	}
}

void SerializeAutoSettings::serializeAll()
{
	std::fstream f(path_, std::fstream::out | std::ios::binary);
	f << isSerializeSettings;
	f << '\n';
	f << getSettingsIrrigationText();
	f.close();
}