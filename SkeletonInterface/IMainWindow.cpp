#include "IMainWindow.h"

using namespace GUI;

IMainWindow *m_pMainWindow;

IMainWindow::IMainWindow()
{
	m_pMainWindow = this;
}

IMainWindow::~IMainWindow()
{
	m_pMainWindow = nullptr;
}

void GUI::Show()
{
	if (!m_pMainWindow)
		ThrowUninitializedClass("IMainWindow");
	m_pMainWindow->Show();
}
