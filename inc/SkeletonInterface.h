#pragma once


// Not intended to be used outside of SkeletonInterface project


#ifdef SKELETONINTERFACE_EXPORT
#define SKELETONINTERFACE_DECLSPEC    __declspec(dllexport)
#else
#define SKELETONINTERFACE_DECLSPEC    __declspec(dllimport)
#endif
