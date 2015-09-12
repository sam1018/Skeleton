#pragma once


#include"../SkeletonInterface.h"
#include <string>
#include <vector>


namespace VT
{
	class SKELETONINTERFACE_DECLSPEC IPlugin
	{
	public:
		virtual ~IPlugin() = 0;

		std::vector<std::string> GetFunctions();

	private:
		virtual std::vector<std::string> GetFunctions_() = 0;
	};
}
