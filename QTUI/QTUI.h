#pragma once

#ifdef QTUI_EXPORT
#define QTUI_DECLSPEC    __declspec(dllexport)
#else
#define QTUI_DECLSPEC    __declspec(dllimport)
#endif
