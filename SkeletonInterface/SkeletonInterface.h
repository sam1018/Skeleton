#pragma once

#include <string>

#ifdef SKELETONINTERFACE_EXPORT
#define SKELETONINTERFACE_DECLSPEC    __declspec(dllexport)
#else
#define SKELETONINTERFACE_DECLSPEC    __declspec(dllimport)
#endif


// Internal Routines
void ThrowUninitializedClass(std::string className);
