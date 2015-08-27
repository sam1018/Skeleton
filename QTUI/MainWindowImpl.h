#pragma once

#include <QtWidgets\QMainWindow>

///////////////////////////////////////////////////////
///     Implementation class for MainWindow       /////
///  So only MainWindow is supposed to include it /////
///////////////////////////////////////////////////////

class MainWindowImpl : public QMainWindow
{
	Q_OBJECT

public:
	MainWindowImpl();
	~MainWindowImpl();

	void Show();

protected:
	void closeEvent(QCloseEvent *event);

//	public slots:
//	void AddCatDebug();
//	void AppendToDebug();
//	void AddCatDebug2();
//	void AppendToDebug2();
//
//private:
//	void AddToolbars();
};
