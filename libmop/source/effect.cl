#ifndef OCL_EXTERNAL_INCLUDE
#define OCL_EXTERNAL_INCLUDE(x) x
#endif

OCL_EXTERNAL_INCLUDE(
__kernel void Blur(__global unsigned char* src, __global unsigned char* dst, int3 size, int half_amount) {

	int x = get_global_id(0);
	int y = get_global_id(1);
	int c = 0;

	int min_x = 0 <= x - half_amount ? x - half_amount : 0;
	int min_y = 0 <= y - half_amount ? y - half_amount : 0;

	int max_x = x + half_amount <= size.x ? x + half_amount : size.x;
	int max_y = y + half_amount <= size.y ? y + half_amount : size.y;

	int xx;
	int yy;
	int data = 0;
	int num = (max_x - min_x) * (max_y - min_y);

	for (c = 0; c < size.z; c++) {

		data = 0;

		for (yy = min_y; yy < max_y; yy++) {
			for (xx = min_x; xx < max_x; xx++) {
				data += src[(xx + yy * size.x) * size.z + c];
			}
		}

		dst[(x + y * size.x) * size.z + c] = data / num;

	}

}
)