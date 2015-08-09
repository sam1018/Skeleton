#pragma once

class FunctionLoadFailedException : public std::exception
{
public:
	FunctionLoadFailedException(const char* const msg) : std::exception{ msg }{}
};

class ModuleLoadException : public std::exception
{
public:
	ModuleLoadException(const char* const msg) : std::exception{ msg }{}
};
