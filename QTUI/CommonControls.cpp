#include "CommonControls.h"
#include <QtWidgets\QFileDialog>


CommonControls::CommonControls()
{
}


CommonControls::~CommonControls()
{
}

void* CommonControls::GetImpl()
{
	// This class don't have an implementation class
	// As it will use all static functions from QT
	return nullptr;
}

std::string CommonControls::GetOpenFileName(UIItem *parent, const std::string &caption,
	const std::string &dir, const std::string &filter,
	std::string *selectedFilter, const int options)
{
	QString filterRes;
	QString res = QFileDialog::getOpenFileName(static_cast<QWidget*>(parent->GetImpl()), 
		caption.c_str(), dir.c_str(), filter.c_str(), &filterRes, 
		static_cast<QFileDialog::Options>(options));

	if(selectedFilter)
		*selectedFilter = filterRes.toStdString();

	return res.toStdString();
}
