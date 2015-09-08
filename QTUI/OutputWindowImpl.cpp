#include "OutputWindowImpl.h"
#include "OutputWindow.h"
#include <QtWidgets\QComboBox>
#include <QtWidgets\QVBoxLayout>
#include <QtWidgets\QPlainTextEdit>


using namespace std;


OutputWindowImpl::OutputWindowImpl(OutputWindow *wnd) :
	QDockWidget("Output Window"),
	comboCatagory{ new QComboBox },
	textEdit{ new QPlainTextEdit },
	outputWindow{ wnd }
{
	setObjectName("Output Window");

	textEdit->setReadOnly(true);

	QVBoxLayout *layout = new QVBoxLayout;

	layout->setSpacing(0);
	layout->setMargin(0);
	layout->setContentsMargins(0, 0, 0, 0);

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
	connect(comboCatagory, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(ComboCategoryChanged(const QString&)));
}


OutputWindowImpl::~OutputWindowImpl()
{
}

void OutputWindowImpl::AddCategory(const string &categoryName)
{
	emit AddCategorySignal(QString(categoryName.c_str()));
}

void OutputWindowImpl::AddCategoryHandler(const QString &categoryName)
{
	comboCatagory->addItem(categoryName);
}

void OutputWindowImpl::Refresh(const string &categoryName, const string &text)
{
	emit RefreshSignal(QString(categoryName.c_str()), QString(text.c_str()));
}

void OutputWindowImpl::SetComboCategoryChangedCallback(std::function<void(const std::string&)> callback)
{
	ComboCategoryChangedCallback = callback;
}

void OutputWindowImpl::RefreshHandler(const QString &categoryName, const QString &text)
{
	comboCatagory->setCurrentText(categoryName);
	textEdit->setPlainText(text);

	//move the cursor to the end of the text
	QTextCursor cursor(textEdit->textCursor());
	cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
	textEdit->setTextCursor(cursor);
}

void OutputWindowImpl::ComboCategoryChanged(const QString &cat)
{
	if(ComboCategoryChangedCallback)
		ComboCategoryChangedCallback(cat.toStdString());
}
