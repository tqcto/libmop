#pragma once

extern "C" {
#include "deflate/define.h"
}

#include "deflate/deflate.hpp"

extern "C" {
#include "xor_shift.h"
#include "wrap.h"
}

#include "winutil.h"

extern "C++" {
#include "reader.hpp"
#include "matrix.hpp"
#include "effect.hpp"
}
