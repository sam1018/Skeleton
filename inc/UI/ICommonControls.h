#pragma once

#include "SkeletonInterface.h"
#include <string>

namespace UI
{
	namespace FileDlg_Options
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

	class SKELETONINTERFACE_DECLSPEC ICommonControls
	{
	public:
		std::string GetOpenFileName(void *parent = nullptr, const std::string &caption = std::string(),
			const std::string &dir = std::string(), const std::string &filter = std::string(),
			std::string *selectedFilter = nullptr, const int options = 0);

	private:
		virtual std::string GetOpenFileName_(void *parent = nullptr, const std::string &caption = std::string(),
			const std::string &dir = std::string(), const std::string &filter = std::string(),
			std::string *selectedFilter = nullptr, const int options = 0) = 0;
	};
}
