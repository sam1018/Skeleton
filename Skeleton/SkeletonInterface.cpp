#include "S"
#include <exception>

void ThrowUninitializedClass(std::string className)
{
	throw std::exception(className + " class is not initialized");
}
