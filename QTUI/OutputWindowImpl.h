#pragma once

#include <QtWidgets\QDockWidget>

class QComboBox;
class QPlainTextEdit;
class OutputWindow;

class OutputWindowImpl : public QDockWidget
{
	Q_OBJECT

public:
	OutputWindowImpl(OutputWindow *wnd);
	~OutputWindowImpl();

	void AddCategory(std::string categoryName);
	void SetCategory(std::string categoryName);

	public slots:
	void UpdateText(const QString& categoryName);

private:
	// although not specifically mentioned in QT documentation,
	// but seems from the QT examples, layout takes ownership 
	// of added widgets
	QComboBox *comboCatagory;
	QPlainTextEdit *textEdit;

	OutputWindow *outputWindow;
};
