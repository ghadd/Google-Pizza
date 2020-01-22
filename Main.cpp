#include <iostream>
#include <numeric>
#include "Input.h"

int main() {
	std::string filenames[] = { "tests\\a_example.in",  
								"tests\\b_small.in",
								"tests\\c_medium.in",
								"tests\\d_quite_big.in",
								"tests\\e_also_big.in"};
	for (int i = 0; i < 3; i++) {
		std::string filename = filenames[i];
		std::fstream test(filename, std::ios_base::in);
		if (!test.is_open()) {
			std::cout << "Error opening test " << "\"" << filename << "\"" << std::endl;
			return 1;
		}
		ULONG M, N;
		test >> M >> N;
		Input input(filename, M, N, test);

		ULONG result = input.compute_max_appr_sum();
		std::cout << result << std::endl;

		test.close();
	}
	return 0;
}