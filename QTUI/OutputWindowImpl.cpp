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

	connect(comboCatagory, SIGNAL(currentTextChanged(const QString&)), this, SLOT(UpdateText(const QString&)));
}


OutputWindowImpl::~OutputWindowImpl()
{
}

void OutputWindowImpl::AddCategory(std::string categoryName)
{
	comboCatagory->addItem(categoryName.c_str());
}

void OutputWindowImpl::SetCategory(std::string categoryName)
{
	comboCatagory->setCurrentText(categoryName.c_str());
}

void OutputWindowImpl::UpdateText(const QString& categoryName)
{
	textEdit->setPlainText(outputWindow->GetTextForCategory(categoryName.toStdString()).c_str());
}
