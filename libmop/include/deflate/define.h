#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifdef MOP_LOG_SHOW
#define DEBUG_LOG(A)	printf(A)
#else
#define DEBUG_LOG(...)
#endif

#ifndef MIN
#define MIN(a, b)  ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#define MAX(a, b)  ((a) < (b) ? (b) : (a))
#endif

#ifndef RANGE
#define RANGE(min, max, value)	((value) < (min) ? (min) : (max) < (value) ? (max) : (value))
#endif

#ifndef MOP_PI
#define MOP_PI 3.14
#endif

#ifndef D2R
#define D2R(_d)	( ((_d) != 0) ? (double)((double)(_d) * (MOP_PI / 180.0)) : 0 )
#endif
#ifndef R2D
#define R2D(_r)	( ((_r) != 0) ? (double)((double)(_r) * (180.0 / MOP_PI)) : 0 )
#endif

#ifndef SIN
#define SIN(_v)	( R2D(sin(D2R(_v))) )
#endif
#ifndef COS
#define COS(_v)	( R2D(cos(D2R(_v))) )
#endif

#ifndef DLL_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(_A) ( sizeof(_A) / sizeof(_A[0]) )
#endif

#ifndef CL_CHECK_ERR
#define CL_CHECK_ERR(func)			\
	if (cl_int err = (func)) {		\
		printf("error:%d\n", err);	\
	}
#endif
