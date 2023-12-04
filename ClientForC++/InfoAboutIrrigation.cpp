#include"InfoAboutIrrigation.h"

InfoAboutIrrigation::InfoAboutIrrigation(HWND& eDit) :itText_("\inf"),itPhoto_("\photo")
{
	textData_.resize(numberFilesDirectory("\inf"));
	photoData_.resize(numberFilesDirectory("\photo"));
	
	textData_[currentElem_] = getTextData();
	photoData_[currentElem_] = getPhotoData();

	SetWindowTextA(eDit, textData_[currentElem_].c_str());
	InvalidateRect(GetParent(eDit), NULL, 1);
	UpdateWindow(GetParent(eDit));
}

InfoAboutIrrigation::~InfoAboutIrrigation()
{
	for (auto& photo : photoData_)
		DeleteObject(photo);
}

std::string InfoAboutIrrigation::getTextData()
{
	std::string data,temp;
	std::fstream fs(itText_->path().string());
	while (!fs.eof())
	{
		std::getline(fs, temp);
		data += temp+ "\r\n";
	}
	fs.close();
	return data;
}

HBITMAP InfoAboutIrrigation::getPhotoData()
{
	std::string path = itPhoto_->path().string();
	return (HBITMAP)LoadImageA(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

std::size_t InfoAboutIrrigation::numberFilesDirectory(std::filesystem::path path)
{
	return std::distance(directory_iterator(path), directory_iterator{});
}



HBITMAP InfoAboutIrrigation::getPhoto()const
{
	return photoData_[currentElem_];
}

void InfoAboutIrrigation::next(HWND& eDit)
{
	if ((currentElem_+1) <= (textData_.size() - 1))
	{
		currentElem_++;
		SetWindowTextA(eDit, " ");
		if (textData_[currentElem_].empty())
		{
			itText_++;
			textData_[currentElem_] = getTextData();
		}
		if (photoData_[currentElem_] == NULL)
		{
			itPhoto_++;
			photoData_[currentElem_] = getPhotoData();
		}
		SetWindowTextA(eDit, textData_[currentElem_].c_str());
		InvalidateRect(GetParent(eDit), NULL, 1);
		UpdateWindow(GetParent(eDit));
	}
}

void InfoAboutIrrigation::previous(HWND& eDit)
{
	if ((currentElem_-1)>=0)
	{
		currentElem_--;
		SetWindowTextA(eDit, " ");
		SetWindowTextA(eDit, textData_[currentElem_].c_str());
		InvalidateRect(GetParent(eDit), NULL, 1);
		UpdateWindow(GetParent(eDit));
	}
}