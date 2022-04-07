#include <iostream>
#include "../include/accelerator.hpp"

using namespace concurrency;
using concurrency::accelerator;

DLL_EXPORT std::vector<accelerator> GetAccelerators(void) {

	std::vector<accelerator> accels;
	accels = accelerator::get_all();

	for (int i = 0; i < accels.size(); i++) {
		std::wcout << i + 1 << "th device = " << accels[i].get_description() << "\n";
	}

	accels.erase(std::remove_if(accels.begin(), accels.end(), [](accelerator& accel) {
		return accel.get_is_emulated();
		}), accels.end());

	return accels;

}
