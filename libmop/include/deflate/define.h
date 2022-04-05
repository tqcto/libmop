#pragma once

#ifndef DLL_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(_A) ( sizeof(_A) / sizeof(_A[0]) )
#endif
