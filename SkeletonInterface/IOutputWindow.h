#pragma once

#include "UIItem.h"
#include "SkeletonInterface.h"

namespace OutWnd
{
	class SKELETONINTERFACE_DECLSPEC IOutputWindow : public UI::UIItem
	{
	public:
		IOutputWindow();
		virtual ~IOutputWindow() = 0;

		void InitializeItem();
		void Cleanup();

		virtual void AddCategory(std::string categoryName) = 0;
		virtual void SetCategory(std::string categoryName) = 0;
		virtual void UpdateText(std::string categoryName) = 0;

		// Throws if categoryName is not a valid category
		std::string GetTextForCategory(std::string categoryName);
	};

	// Common Categories
	extern const std::string SKELETONINTERFACE_DECLSPEC OutWndPluginExplorerCategory;

	// Output Window Category ID
	using OutWndCatID = int;

	// You need the OutWndCatID to display in output window
	// One category name can be registered only once
	// Calling this function using same category name multiple times will return same OutWndCatID
	// Thread safety: Thread safe through locking
	OutWndCatID SKELETONINTERFACE_DECLSPEC RegisterOutputWindowCategory(std::string categoryName);

	// Thread safety: Thread safe through locking
	void SKELETONINTERFACE_DECLSPEC OutputWindowSetText(OutWndCatID id, std::string text, bool append, bool makeCurrrentCategory);

	template< class Elem = char, class Tr = std::char_traits< Elem > >
	class StdRedirector : public std::basic_streambuf< Elem, Tr >
	{
	public:
		StdRedirector(std::ostream &a_Stream, OutWnd::OutWndCatID wnd) :
			m_Stream{ a_Stream },
			m_pBuf{ m_Stream.rdbuf(this) },
			outWndId{ wnd }
		{}

		~StdRedirector()
		{
			m_Stream.rdbuf(m_pBuf);
		}

		/**
		* Override xsputn and make it forward data to the callback function.
		*/
		std::streamsize xsputn(const Elem* _Ptr, std::streamsize _Count)
		{
			OutWnd::OutputWindowSetText(outWndId, _Ptr, true, true);
			return _Count;
		}

		/**
		* Override overflow and make it forward data to the callback function.
		*/
		typename Tr::int_type overflow(typename Tr::int_type v)
		{
			Elem ch = Tr::to_char_type(v);
			OutWnd::OutputWindowSetText(outWndId, &ch, true, true);
			return Tr::not_eof(v);
		}

	protected:
		std::basic_ostream<Elem, Tr> &m_Stream;
		std::streambuf *m_pBuf;
		OutWnd::OutWndCatID outWndId;
	};
}
