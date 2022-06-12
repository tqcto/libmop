#pragma once
#include "deflate/define.h"

#ifndef INC_MOP_XOR_SHIFT_H
#define INC_MOP_XOR_SHIFT_H

#define XS_SRAND		init_xorShift
#define XS_RAND			xorShift
#define XS_RAND_MAX		0x7FFF

/**
* @def
* @brief 最大値と最小値を決めて乱数を発生させます。
* @param LO 最小値
* @param HI 最大値
*/
#define XSR_RAND(LO, HI)	(XS_RAND() * (HI - LO + 1.0) / (1.0 + XS_RAND_MAX))
/**
* @def
* @brief 最大値を決めて乱数を発生させます。
* @param HI 最大値
*/
#define XSM_RAND(HI)		(XS_RAND() * (HI + 1.0) / (1.0 + XS_RAND_MAX))

DLL_EXPORT unsigned int xorShift(void);
DLL_EXPORT double xorShiftDouble(void);
DLL_EXPORT void init_xorShift(unsigned int s);

#endif
