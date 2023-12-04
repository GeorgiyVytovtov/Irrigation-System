#pragma once
#include<fstream>
#include<Windows.h>
#include<array>
#include<filesystem>
#include<iostream>
#include <string>

using std::filesystem::directory_iterator;

class InfoAboutIrrigation 
{
private:
	std::vector<std::string> textData_;
	std::vector <HBITMAP> photoData_;
	int currentElem_ = 0;
	std::string getTextData();
	HBITMAP getPhotoData();
	std::size_t numberFilesDirectory(std::filesystem::path path);
	directory_iterator itText_;
	directory_iterator itPhoto_;
public:
	HBITMAP getPhoto()const;
	InfoAboutIrrigation(HWND& eDit);
	~InfoAboutIrrigation();
	void next(HWND& eDit);
	void previous(HWND& eDit);
};
