#pragma once

#include <QtWidgets\QMainWindow>

class OpenGLWindow;

class MainWindowImpl : public QMainWindow
{
	Q_OBJECT

public:
	MainWindowImpl(OpenGLWindow *pOpenGLWindow);
	~MainWindowImpl();

	void Show();

private:
	void AddToolbars();
	void AddTBBMonitors(QToolBar *toolbar);

	private slots:
	void ShowWindow(int monitorIndex);

private:
	// I am storing the screens list internally, rather than fetching from QApplication every time
	// So that, the time screens combo is populated, and the time a combo item is clicked, there is
	// no descrepency between the list
	// TODO: handle monitor events to update the screens combo run time
	QList <QScreen*> m_Screens;
};
