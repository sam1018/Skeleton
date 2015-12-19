#pragma once

#include <QtWidgets\QMainWindow>

///////////////////////////////////////////////////////
///     Implementation class for MainWindow       /////
///  So only MainWindow is supposed to include it /////
///////////////////////////////////////////////////////

class MainWindowImpl : public QMainWindow
{
public:
	MainWindowImpl();
	~MainWindowImpl();

	void Show();

protected:
	void closeEvent(QCloseEvent *event);
};
