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
			bool makeCurrrentCategory, const char *file, int line);

		void SetOutputWindow(UI::IOutputWindow *wnd);

	private:
		virtual MsgCatID RegisterMessageCategory_(const std::string &categoryName) = 0;
		virtual void PrintMessage_(MsgCatID id, const std::string &text, 
			bool append, bool makeCurrrentCategory, const char *file, int line) = 0;
		virtual void SetOutputWindow_(UI::IOutputWindow *wnd) = 0;
	};


	template< class Elem = char, class Tr = std::char_traits< Elem > >
	class StdRedirector : public std::basic_streambuf< Elem, Tr >
	{
	public:
		StdRedirector(std::ostream &a_Stream, MsgCatID wnd) :
			m_Stream{ a_Stream },
			outWndId{ wnd }
		{
			m_pBuf = m_Stream.rdbuf(this);
		}

		~StdRedirector()
		{
			m_Stream.rdbuf(m_pBuf);
		}

		/**
		* Override xsputn and make it forward data to the callback function.
		*/
		std::streamsize xsputn(const Elem *_Ptr, std::streamsize _Count)
		{
			PRINT_MESSAGE(outWndId, _Ptr, true, true)
			return _Count;
		}

		/**
		* Override overflow and make it forward data to the callback function.
		*/
		typename Tr::int_type overflow(typename Tr::int_type v)
		{
			std::string s;
			s += Tr::to_char_type(v);
			PRINT_MESSAGE(outWndId, s, true, true)
			return Tr::not_eof(v);
		}

	private:
		std::basic_ostream<Elem, Tr> &m_Stream;
		std::streambuf *m_pBuf;
		MsgCatID outWndId;
	};
}
