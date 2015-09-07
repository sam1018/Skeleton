#include "CommonControls.h"
#include <QtWidgets\QFileDialog>

using namespace std;

CommonControls::CommonControls()
{
}


CommonControls::~CommonControls()
{
}

string CommonControls::GetOpenFileName_(void *parent, const string &caption,
	const string &dir, const string &filter,
	string *selectedFilter, const int options)
{
	QString filterRes;
	QString res = QFileDialog::getOpenFileName(static_cast<QWidget*>(parent), 
		caption.c_str(), dir.c_str(), filter.c_str(), &filterRes, 
		static_cast<QFileDialog::Options>(options));

	if(selectedFilter)
		*selectedFilter = filterRes.toStdString();

	return res.toStdString();
}
