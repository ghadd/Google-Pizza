#include <iostream>
#include "Input.h"

int main() {
	std::fstream test("tests\\c_medium.in", std::ios_base::in);
	ULONG M, N;
	test >> M >> N;
	Input input(M, N, test);

	ULONG result = input.compute_max_appr_sum();
	std::cout << result;

	test.close();

	return 0;
}