#pragma once
#include<fstream>

struct Settings
{
	bool isAuto, isManual, isStarted, isSettingsManual, isSettingsAuto, isSettingsConnection, isUpdata;
	std::string ipAddress;
	size_t port=0;
	Settings()
	{
		std::fstream settings("MainSettings.bin", std::fstream::in | std::fstream::app| std::ios::binary);
		settings >> isAuto >> isManual >> isStarted >> isSettingsManual >> isSettingsAuto >> isSettingsConnection>> isUpdata;

		if (isSettingsConnection)
		{
			settings >> ipAddress >> port;
		}
		settings.close();
	}
	~Settings()
	{
		std::fstream settings("MainSettings.bin", std::fstream::out | std::ios::binary);
		settings << isAuto << '\n' << isManual << '\n' << isStarted << '\n' << isSettingsManual << '\n' << isSettingsAuto << '\n' << isSettingsConnection << '\n' << isUpdata;

		if (isSettingsConnection)
		{
			settings << '\n' << ipAddress << '\n' << port;
		}
		settings.close();
	}
};
