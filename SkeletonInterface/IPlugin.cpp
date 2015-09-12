#include "Vitals\IPlugin.h"


using namespace VT;
using namespace std;


IPlugin::~IPlugin()
{
}

vector<string> IPlugin::GetFunctions()
{
	return GetFunctions_();
}
