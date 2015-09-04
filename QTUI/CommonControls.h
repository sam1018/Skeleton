#pragma once

#include "UI/CommonControls.h"

class CommonControls : public CommCtrls::ICommonControls
{
public:
	CommonControls();
	~CommonControls();

	void* GetImpl();

	std::string GetOpenFileName(UIItem *parent = nullptr, const std::string &caption = std::string(),
		const std::string &dir = std::string(), const std::string &filter = std::string(),
		std::string *selectedFilter = nullptr, const int options = 0);
};
