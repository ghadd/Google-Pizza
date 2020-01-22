#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>

typedef unsigned long ULONG;

class Input {
private:
	std::string filename;
	ULONG max_of_pieces, num_of_variations;
	std::vector<ULONG> slices;

public:
	Input(std::string, ULONG&, ULONG&, std::fstream&);
	~Input();
	bool is_valid();
	void display();
	ULONG compute_max_appr_sum();
};

std::vector<std::vector<bool>> get_subset_matrix(std::vector<ULONG> set, ULONG n, ULONG sum, std::map<int, int>& ways);
void write_file(std::string filename, std::vector<ULONG> set, std::vector<ULONG> selected);