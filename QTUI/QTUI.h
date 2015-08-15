#pragma once

#ifdef QTUI_EXPORTS
#define QTUI_DECLSPEC    __declspec(dllexport)
#else
#define QTUI_DECLSPEC    __declspec(dllimport)
#endif
