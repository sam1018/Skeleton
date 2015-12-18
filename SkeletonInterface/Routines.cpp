#include "Routines.h"
#include <boost\filesystem.hpp>

using namespace std;
using namespace Routines;
using namespace boost::filesystem;

path binFilePath;

constexpr auto settingsDirName{ "/Settings" };

void Routines::SetBinFilePath(string path)
{
	binFilePath /= path;
}

string Routines::GetBinDirectory()
{
	return binFilePath.parent_path().generic_string();
}

string Routines::GetUserDir()
{
	path p;

#ifdef _WIN32
	char *buffer;
	_dupenv_s(&buffer, NULL, "UserProfile");
	p /= buffer;
	free(buffer);
#else
	p /= getnev("HOME");
#endif

	p /= GetApplicationName();

	create_directory(p);

	return p.generic_string();
}

string Routines::GetUserSettingsDir()
{
	path p(GetUserDir());

	p /= settingsDirName;

	create_directory(p);

	return p.generic_string();
}

string Routines::GetFactorySettingsDir()
{
	path p(GetBinDirectory());

	p /= "../../";

	return p.generic_string();
}

string Routines::GetSettingsFileFullPath_Save(string fileName)
{
	path p(GetUserSettingsDir());

	p /= fileName;

	return p.generic_string();
}

string Routines::GetSettingsFileFullPath_Load(string fileName)
{
	path p(GetUserSettingsDir());

	p /= fileName;

	if (!exists(p))
	{
		p = GetFactorySettingsDir();
		p /= fileName;
	}

	if (!exists(p))
		throw exception((fileName + " not found").c_str());

	return p.generic_string();
}

string Routines::GetApplicationName()
{
	return binFilePath.stem().generic_string();
}

string Routines::GetCompanyName()
{
	return "HOME";
}

string Routines::GetFileNameFromPath(string filepath)
{
	path p(filepath);

	return p.stem().generic_string();
}

bool Routines::IsSamePath(string path1, string path2)
{
	path p1(path1), p2(path2);

	return p1 == p2;
}

std::string Routines::GlobalSettingsFilePath()
{
	const string settingsFile{ "SkeletonSettings.xml" };
	return GetSettingsFileFullPath_Load(settingsFile);
}
