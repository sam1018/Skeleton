#pragma once

#include <QtWidgets\QDockWidget>

class QComboBox;
class QPlainTextEdit;
class OutputWindow;

class OutputWindowImpl : public QDockWidget
{
	Q_OBJECT

public:
	explicit OutputWindowImpl(OutputWindow *wnd);
	~OutputWindowImpl();

	void AddCategory(const std::string &categoryName);
	void Refresh(const std::string &categoryName, const std::string &text);

	public slots:
	void AddCategoryHandler(const QString &categoryName);
	void RefreshHandler(const QString &categoryName, const QString &text);

signals:
	void AddCategorySignal(const QString &categoryName);
	void RefreshSignal(const QString &categoryName, const QString &text);

private:
	// although not specifically mentioned in QT documentation,
	// but seems from the QT examples, layout takes ownership 
	// of added widgets
	QComboBox *comboCatagory;
	QPlainTextEdit *textEdit;

	OutputWindow *outputWindow;
};
