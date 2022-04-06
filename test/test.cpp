#include <stdio.h>
#include <stdlib.h>

#include "libmop.h"

int main(void) {

	mop::matrix mat(1920, 1080, mop::color_type::RGBA);

	if (mat.empty()) {
		printf("empty.\n");
		return 1;
	}

	printf("w:%d h:%d c:%d\n", mat.width(), mat.height(), mat.channel());

	return 0;

}
