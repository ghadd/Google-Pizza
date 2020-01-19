#include <iostream>
#include "Input.h"

int main() {
	std::fstream test("tests\\a_example.in", std::ios_base::in);
	ULONG M, N;
	test >> M >> N;
	Input input(M, N, test);
	
	input.display();

	ULONG result = input.compute_max_appr_sum();
	std::cout << result;

	return 0;
}