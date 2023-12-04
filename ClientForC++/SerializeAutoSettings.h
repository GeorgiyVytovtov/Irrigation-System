#pragma once
#include"Serialize.h"

class SerializeAutoSettings :public Serialize
{
private:
	std::string path_ = "Auto.bin";
	static SerializeAutoSettings* serializeAuto_;
	void parse(std::string data);
public:
	SerializeAutoSettings();
	~SerializeAutoSettings();
	void serializeAll()override;
	static SerializeAutoSettings* getSerializ();
};