#include "IMainWindow.h"

using namespace MW;

IMainWindow *m_pMainWindow;

IMainWindow::IMainWindow()
{
	m_pMainWindow = this;
}

IMainWindow::~IMainWindow()
{
	m_pMainWindow = nullptr;
}

void MW::Show()
{
	if (!m_pMainWindow)
		ThrowUninitializedClass("IMainWindow");
	m_pMainWindow->Show();
}
