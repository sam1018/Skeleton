#pragma once

#include "SkeletonInterface.h"
#include <string>
#include <functional>

namespace UI
{
	class SKELETONINTERFACE_DECLSPEC IOutputWindow
	{
	public:
		IOutputWindow();
		virtual ~IOutputWindow() = 0;

		// Threading instructions for AddCategory and Refresh for the implementer:
		// These two functions may get called from another thread than the GUI thread
		// So take necessary precautions if this is a problem in your GUI toolkit (ex: QT)
		//
		// It is ok, if implementation queues this operation for later execution, as long as
		// clients are able to call Refresh immediately after AddCategory
		//
		// For example, if implementation queues this operation for later execution,
		// and client calls Refresh right after calling AddCategory, and in the GUI thread,
		// AddCategory gets called before Refresh, then there is no problem
		// But if Refresh gets called before AddCategory, then that's a problem implementar needs to take care
		void AddCategory(const std::string &categoryName);
		void Refresh(const std::string &categoryName, const std::string &text);

		void SetComboCategoryChangedCallback(std::function<void(const std::string&)> callback);

	private:
		virtual void AddCategory_(const std::string &categoryName) = 0;
		virtual void Refresh_(const std::string &categoryName, const std::string &text) = 0;
		virtual void SetComboCategoryChangedCallback_(std::function<void(const std::string&)> callback) = 0;
	};
}
