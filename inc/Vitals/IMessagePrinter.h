#pragma once

#include "../SkeletonInterface.h"
#include "../UI/IOutputWindow.h"
#include "../Settings.h"
#include"../Routines.h"
#include <string>


#define PRINT_MESSAGE(id, text, append, makeCurrentCategory) \
VT::GetMessagePrinter()->PrintMessage(id, text, append, makeCurrentCategory, __FILE__, __LINE__);


namespace VT
{
	struct MessagePrinterSettings
	{
		Settings::AttribAccessor accessor;
		bool showFileName;
		bool showLineNumber;
		bool appendNewLine;

		MessagePrinterSettings()
		{
			accessor.RegisterItem(showFileName, "SkeletonSettings.MessagePrinter.ShowFileName");
			accessor.RegisterItem(showLineNumber, "SkeletonSettings.MessagePrinter.ShowLineNumber");
			accessor.RegisterItem(appendNewLine, "SkeletonSettings.MessagePrinter.AppendNewLine");

			accessor.Load(Routines::GlobalSettingsFilePath());
		}
	};



	// Message Category ID
	using MsgCatID = int;

	// Common Categories
	extern MsgCatID SKELETONINTERFACE_DECLSPEC MsgCat_PluginExplorer;
	extern MsgCatID SKELETONINTERFACE_DECLSPEC MsgCat_ErrorMsg;



	// Simply delete IRedirHandler when you are done redirecting
	class SKELETONINTERFACE_DECLSPEC IRedirHandler
	{
	public:
		virtual ~IRedirHandler() = 0;
		void Pause();
		void Resume();

	private:
		virtual void Pause_() = 0;
		virtual void Resume_() = 0;
	};




	class SKELETONINTERFACE_DECLSPEC IMessagePrinter
	{
	public:
		IMessagePrinter();
		virtual ~IMessagePrinter() = 0;

		// You need the MsgCatID to display in output window
		// One category name can be registered only once
		// Calling this function using same category name multiple times will return same MsgCatID
		// Thread safety: Thread safe through locking
		MsgCatID RegisterMessageCategory(const std::string &categoryName);

		// Thread safety: Thread safe through locking
		void PrintMessage(MsgCatID id, const std::string &text, bool append, 
			bool makeCurrrentCategory, const char *file = nullptr, int line = -1);

		void SetOutputWindow(UI::IOutputWindow *wnd);

		std::unique_ptr<IRedirHandler> RedirectStream(std::ostream &stream, MsgCatID cat);

	private:
		virtual MsgCatID RegisterMessageCategory_(const std::string &categoryName) = 0;
		virtual void PrintMessage_(MsgCatID id, const std::string &text, 
			bool append, bool makeCurrrentCategory, const char *file, int line) = 0;
		virtual void SetOutputWindow_(UI::IOutputWindow *wnd) = 0;
		virtual std::unique_ptr<IRedirHandler> RedirectStream_(std::ostream &stream, MsgCatID cat) = 0;
	};
}
