#pragma once

extern "C" {
#include "deflate/define.h"
#include "xor_shift.h"
#include "wrap.h"
}

#include "winutil.h"

extern "C++" {
#include "deflate/deflate.hpp"
#include "reader.hpp"
#include "matrix.hpp"
#include "effect.hpp"
#include "filter.hpp"
}
