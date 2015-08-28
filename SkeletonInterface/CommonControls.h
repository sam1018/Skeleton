#pragma once

#include "UIItem.h"
#include "SkeletonInterface.h"

namespace CommCtrls
{
	class SKELETONINTERFACE_DECLSPEC ICommonControls : public UI::UIItem
	{
	public:
		void InitializeItem();
		void Cleanup();

		virtual std::string GetOpenFileName(UIItem *parent = nullptr, const std::string &caption = std::string(),
			const std::string &dir = std::string(), const std::string &filter = std::string(),
			std::string *selectedFilter = nullptr, const int options = 0) = 0;
	};

	// Helper functions to UI controls
	// Updated on demand
	namespace FileDialog
	{
		namespace Options
		{
			constexpr int ShowDirsOnly = 0x00000001;
			constexpr int DontResolveSymlinks = 0x00000002;
			constexpr int DontConfirmOverwrite = 0x00000004;
			constexpr int DontUseSheet = 0x00000008;
			constexpr int DontUseNativeDialog = 0x00000010;
			constexpr int ReadOnly = 0x00000020;
			constexpr int HideNameFilterDetails = 0x00000040;
			constexpr int DontUseCustomDirectoryIcons = 0x00000080;
		};

		std::string GetOpenFileName(UI::UIItem *parent = nullptr, const std::string &caption = std::string(),
			const std::string &dir = std::string(), const std::string &filter = std::string(),
			std::string *selectedFilter = nullptr, const int options = 0);
	}
}
