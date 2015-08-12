#pragma once

class PluginFailedException : public std::exception
{
public:
	PluginFailedException(const char* const msg) : std::exception{ msg }{}
};
