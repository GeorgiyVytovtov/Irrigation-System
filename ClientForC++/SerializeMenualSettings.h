#pragma once
#include"Serialize.h"

class SerializeMenualSettings :public Serialize
{
private:
	std::string path_ = "Menual.bin";
	static SerializeMenualSettings* serializeMenual_;
	void parse(std::string msg);
public:
	SerializeMenualSettings();
	~SerializeMenualSettings();
	void serializeAll()override;
	static SerializeMenualSettings* getSerializ();
};