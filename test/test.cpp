#include <stdio.h>
#include <stdlib.h>

#include "libmop.h"

int main(void) {

	int value = 20,
		max = 19;

	printf("v:%d max:%d a:%d\n", value, max, mirror(value, max));

	return 0;

}
