#pragma once
#include "deflate/define.h"

#include <amp.h>
#include <vector>

DLL_EXPORT std::vector<concurrency::accelerator> GetAccelerators(void);
