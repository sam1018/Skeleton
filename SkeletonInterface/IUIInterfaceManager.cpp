#include "UI\IUIInterfaceManager.h"

using namespace UI;

namespace UI
{
	class UIInterfaceMngrAccessor
	{
	public:
		void SetUIInterfaceManager(IUIInterfaceManager *val)
		{
			uiInterfaceManager = val;
		}

	private:
		IUIInterfaceManager *uiInterfaceManager;

	} uiInterfaceMngrAccessor;
}

void UI::SetUIInterfaceManager(IUIInterfaceManager *uiInterfaceManager)
{
	uiInterfaceMngrAccessor.SetUIInterfaceManager(uiInterfaceManager);
}
