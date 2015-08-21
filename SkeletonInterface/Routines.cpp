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

	p /= binFilePath.stem();

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
