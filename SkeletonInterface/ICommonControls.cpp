#include "UI/ICommonControls.h"

using namespace UI;

std::string ICommonControls::GetOpenFileName(void *parent, const std::string & caption,
	const std::string & dir, const std::string & filter, 
	std::string * selectedFilter, const int options)
{
	return GetOpenFileName_(parent, caption, dir, filter, selectedFilter, options);
}
