#pragma once

#include <string>

#ifdef SKELETONINTERFACE_EXPORT
#define SKELETONINTERFACE_DECLSPEC    __declspec(dllexport)
#else
#define SKELETONINTERFACE_DECLSPEC    __declspec(dllimport)
#endif

void ThrowUninitializedClass(std::string className);