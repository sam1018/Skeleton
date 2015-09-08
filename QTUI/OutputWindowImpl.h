#pragma once

#include <functional>
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
	void SetComboCategoryChangedCallback(std::function<void(const std::string&)> callback);

	public slots:
	void AddCategoryHandler(const QString &categoryName);
	void RefreshHandler(const QString &categoryName, const QString &text);
	void ComboCategoryChanged(const QString &cat);

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

	std::function<void(const std::string&)> ComboCategoryChangedCallback;
};
