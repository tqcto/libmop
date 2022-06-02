#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef DLL_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(_A) ( sizeof(_A) / sizeof(_A[0]) )
#endif
