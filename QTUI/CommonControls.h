#pragma once

#include "UI/ICommonControls.h"

class CommonControls : public UI::ICommonControls
{
public:
	CommonControls();
	~CommonControls();

private:
	virtual std::string GetOpenFileName_(void *parent = nullptr, const std::string &caption = std::string(),
		const std::string &dir = std::string(), const std::string &filter = std::string(),
		std::string *selectedFilter = nullptr, const int options = 0);
};
