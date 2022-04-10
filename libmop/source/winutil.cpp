#include "../include/winutil.h"

DLL_EXPORT HWND make_new_window(void) {

	HINSTANCE hinst = GetModuleHandle(NULL);

	TCHAR name[] = TEXT("libmop");
	
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinst;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = name;

	if (!RegisterClass(&wc)) return NULL;

	HWND hwnd = CreateWindow(
		name, TEXT("title"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL,
		hinst, NULL);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	return hwnd;

}

DLL_EXPORT void view_data(HWND hwnd, unsigned char** data, int width, int height, int channel) {

	RECT rec;
	GetWindowRect(hwnd, &rec);

	HDC hdc = GetDC(hwnd);

	BITMAPINFO info;
	info.bmiHeader.biBitCount = 24;
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = -height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biCompression = BI_RGB;
	info.bmiHeader.biClrImportant = 0;
	info.bmiHeader.biClrUsed = 0;
	info.bmiHeader.biSizeImage = 0;
	info.bmiHeader.biXPelsPerMeter = 0;
	info.bmiHeader.biYPelsPerMeter = 0;

	StretchDIBits(
		hdc,
		0, 0,
		rec.right, rec.bottom,
		0, 0,
		width, height,
		*data,
		&info,
		DIB_RGB_COLORS,
		SRCCOPY
	);

}
