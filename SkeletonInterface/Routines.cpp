#include "Routines.h"
#include <boost\filesystem.hpp>

using namespace boost::filesystem;

path binFilePath;

constexpr auto settingsDirName{ "/Settings" };

void Routines::SetBinFilePath(std::string path)
{
	binFilePath /= path;
}

std::string Routines::GetUserDir()
{
	path p;

#ifdef _WIN32
	char *buffer;
	_dupenv_s(&buffer, NULL, "UserProfile");
	p /= buffer;
	free(buffer);
#else
	p /= std::getnev("HOME");
#endif

	p /= GetApplicationName();

	create_directory(p);

	return p.generic_string();
}

std::string Routines::GetUserSettingsDir()
{
	path p(GetUserDir());

	p /= settingsDirName;

	create_directory(p);

	return p.generic_string();
}

std::string Routines::GetFactorySettingsDir()
{
	path p(binFilePath.parent_path());

	p /= "../";
	p /= settingsDirName;

	create_directory(p);

	return p.generic_string();
}

std::string Routines::GetSettingsFileFullPath_Save(std::string fileName)
{
	path p(GetUserSettingsDir());

	p /= fileName;

	return p.generic_string();
}

std::string Routines::GetSettingsFileFullPath_Load(std::string fileName)
{
	path p(GetUserSettingsDir());

	p /= fileName;

	if (!exists(p))
	{
		p = GetFactorySettingsDir();
		p /= fileName;
	}

	if (!exists(p))
		throw std::exception((fileName + " not found").c_str());

	return p.generic_string();
}

std::string Routines::GetApplicationName()
{
	return binFilePath.stem().generic_string();
}

std::string Routines::GetCompanyName()
{
	return "HOME";
}

std::string Routines::GetFileNameFromPath(std::string filepath)
{
	path p(filepath);

	return p.stem().generic_string();
}

bool Routines::IsSamePath(std::string path1, std::string path2)
{
	path p1(path1), p2(path2);

	return p1 == p2;
}
