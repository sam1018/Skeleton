#include "MainWindow.h"
#include <QtWidgets\qmainwindow.h>
#include <QtWidgets\QtWidgets>

struct MainWindow::ImplData
{
	QMainWindow mainWnd;
};

MainWindow::MainWindow() : m_pImplData{ std::make_unique <ImplData> () }
{
	CreateToolbars();
}


MainWindow::~MainWindow()
{
}

void MainWindow::Show()
{
	m_pImplData->mainWnd.showMaximized();
}

void MainWindow::CreateToolbars()
{
	QToolBar *viewsTB = m_pImplData->mainWnd.addToolBar("Views");

	QComboBox *comboScreens = new QComboBox;

	for (auto* screen : QApplication::screens())
		comboScreens->addItem(screen->name());

	viewsTB->addWidget(comboScreens);
}
