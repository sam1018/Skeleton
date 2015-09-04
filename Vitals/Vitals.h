#pragma once

#ifdef VITALS_EXPORTS
#define VITALS_DECLSPEC    __declspec(dllexport)
#else
#define VITALS_DECLSPEC    __declspec(dllimport)
#endif
