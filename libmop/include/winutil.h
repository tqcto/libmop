#pragma once
#include <windows.h>
#include "deflate/define.h"

//extern "C" {
	DLL_EXPORT HWND make_new_window(WNDPROC proc = nullptr);
//}

DLL_EXPORT void view_data(HWND hwnd, void** data, int width, int height, int channel);
