#include "UI/ICommonControls.h"

using namespace UI;
using namespace std;

string ICommonControls::GetOpenFileName(void *parent, const string & caption,
	const string & dir, const string & filter, 
	string * selectedFilter, const int options)
{
	return GetOpenFileName_(parent, caption, dir, filter, selectedFilter, options);
}
