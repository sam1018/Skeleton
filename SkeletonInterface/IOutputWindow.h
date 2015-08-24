#pragma once

#include "SkeletonInterface.h"

namespace GUI
{
	class SKELETONINTERFACE_DECLSPEC IOutputWindow
	{
	public:
		IOutputWindow();
		virtual ~IOutputWindow() = 0;

		virtual void AddCategory(std::string categoryName) = 0;
		virtual void SetCategory(std::string categoryName) = 0;
		virtual void UpdateText(std::string categoryName) = 0;

		// Throws if categoryName is not a valid category
		std::string GetTextForCategory(std::string categoryName);
	};
}

namespace OutWnd
{
	// Output Window Category ID
	using OutWndCatID = int;

	// You need the OutWndCatID to display in output window
	// One category name can be registered only once
	// Calling this function using same category name multiple times will return same OutWndCatID
	// Thread safety instruction: not thread safe
	OutWndCatID SKELETONINTERFACE_DECLSPEC RegisterOutputWindowCategory(std::string categoryName);

	// Thread safety instruction: You can call OutputWindowSetText from multiple threads,
	// as long as you use different id
	// throws if the category is not present
	void SKELETONINTERFACE_DECLSPEC OutputWindowSetText(OutWndCatID id, std::string text, bool append, bool makeCurrrentCategory);
}
