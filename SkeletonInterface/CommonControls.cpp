#include "CommonControls.h"

using namespace CommCtrls;


ICommonControls *commonControls;


void ICommonControls::InitializeItem()
{
	commonControls = this;
}

void ICommonControls::Cleanup()
{
	commonControls = nullptr;
}

std::string CommCtrls::FileDialog::GetOpenFileName(UI::UIItem * parent, const std::string & caption,
	const std::string & dir, const std::string & filter, 
	std::string * selectedFilter, const int options)
{
	if (!commonControls)
		throw std::exception("CommonControls object is not valid");

	return commonControls->GetOpenFileName(parent, caption, dir, filter, selectedFilter, options);
}
