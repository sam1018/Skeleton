#include "OutputWindowImpl.h"
#include "OutputWindow.h"
#include <QtWidgets\QVBoxLayout>
#include <QtWidgets\QComboBox>
#include <QtWidgets\QPlainTextEdit>


OutputWindowImpl::OutputWindowImpl(OutputWindow *wnd) :
	QDockWidget("Output Window"),
	comboCatagory{ new QComboBox },
	textEdit{ new QPlainTextEdit },
	outputWindow{ wnd }
{
	setObjectName("Output Window");

	textEdit->setReadOnly(true);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(comboCatagory);
	layout->addWidget(textEdit);

	// We need to create a new widget, with proper layout
	// and set it to the dock widget
	// And again, not mentioned explicitly in documentation,
	// but it seems, dock widget takes ownership of widget
	QWidget *widget = new QWidget(this);
	widget->setLayout(layout);
	setWidget(widget);

	// AddCategory and Refresh may get called from other thread than the GUI thread
	// The below signal slot mechanism makes sure it is handled in the main thread
	connect(this, SIGNAL(AddCategorySignal(const QString&)), this, SLOT(AddCategoryHandler(const QString&)));
	connect(this, SIGNAL(RefreshSignal(const QString&, const QString&)), this, SLOT(RefreshHandler(const QString&, const QString&)));
}


OutputWindowImpl::~OutputWindowImpl()
{
}

void OutputWindowImpl::AddCategory(const std::string &categoryName)
{
	emit AddCategorySignal(QString(categoryName.c_str()));
}

void OutputWindowImpl::AddCategoryHandler(const QString &categoryName)
{
	comboCatagory->addItem(categoryName);
}

void OutputWindowImpl::Refresh(const std::string &categoryName, const std::string &text)
{
	emit RefreshSignal(QString(categoryName.c_str()), QString(text.c_str()));
}

void OutputWindowImpl::RefreshHandler(const QString &categoryName, const QString &text)
{
	comboCatagory->setCurrentText(categoryName);
	textEdit->setPlainText(text);
}
