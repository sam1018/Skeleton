#include "CommonControls.h"
#include <QtWidgets\QFileDialog>


CommonControls::CommonControls()
{
}


CommonControls::~CommonControls()
{
}

std::string CommonControls::GetOpenFileName_(void *parent, const std::string &caption,
	const std::string &dir, const std::string &filter,
	std::string *selectedFilter, const int options)
{
	QString filterRes;
	QString res = QFileDialog::getOpenFileName(static_cast<QWidget*>(parent), 
		caption.c_str(), dir.c_str(), filter.c_str(), &filterRes, 
		static_cast<QFileDialog::Options>(options));

	if(selectedFilter)
		*selectedFilter = filterRes.toStdString();

	return res.toStdString();
}
