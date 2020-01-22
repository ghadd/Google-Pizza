#pragma once
#include "Input.h"

Input::Input(std::string _filename, ULONG& _max_of_pieces, ULONG& _num_of_variations, std::fstream& file) {
	this->filename = _filename;
	this->max_of_pieces = _max_of_pieces;
	this->num_of_variations = _num_of_variations;
	this->slices.resize(this->num_of_variations);
	ULONG tmp;
	for (ULONG i = 0; i < this->num_of_variations; i++) {
		file >> tmp;
		this->slices.at(i) = tmp;
	}
}

Input::~Input() {};

bool Input::is_valid() {
	ULONG prev = 0;
	for (auto it = this->slices.begin(); it != this->slices.end(); it++) {
		if (*it < prev) {
			return false;
		}
		prev = *it;
	}
	return true;
}

void Input::display() {
	if (!this->is_valid()) {
		std::cout << "Invalid input." << std::endl;
	}
	else {
		for (auto it = this->slices.begin(); it != this->slices.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
}

ULONG Input::compute_max_appr_sum() {
	if (this->max_of_pieces * this->num_of_variations < (ULONG)1e8) {
		try {
			std::map<int, int> ways;
			std::vector<std::vector<bool>> subset_matrix = get_subset_matrix(this->slices, \
				this->num_of_variations, this->max_of_pieces, ways);
			ULONG res = this->max_of_pieces;
			while (!subset_matrix[this->num_of_variations][res]) {
				res--;
			}

			//run backtrack
			std::vector<ULONG> selected;
			int res_tracker = res;
			while (res_tracker != 0) {
				selected.push_back(ways.at(res_tracker));
				res_tracker -= ways.at(res_tracker);
			}
			std::reverse(selected.begin(), selected.end());

			write_file(this->filename.substr(0, this->filename.find('.')) + ".out", \
				this->slices, selected);

			return res;
		}
		catch (std::exception) {
			std::cout << "Exception caught" << std::endl;
			return 0;
		}
	}
	else {
		std::cout << "Running simplified algorithm" << std::endl;
		std::vector<ULONG> best_result = { 0 };
		ULONG start_from = this->num_of_variations - 1;
		ULONG end_from = 99 * num_of_variations / 100 - 1;
		for (; start_from != end_from; start_from--) {
			ULONG pos = start_from;
			std::vector<ULONG> result;
			while (true) {
				if (summed(result) + this->slices[pos] <= this->max_of_pieces) {
					result.push_back(this->slices[pos]);
				}
				if (pos == 0) break;
				pos--;
			}

			if (summed(result) > summed(best_result)) {
				best_result = result;
			}
			if (summed(result) == this->max_of_pieces) break;
		}

		std::reverse(best_result.begin(), best_result.end());
		write_file(this->filename.substr(0, this->filename.find('.')) + ".out", \
			this->slices, best_result);
		return summed(best_result);
	}
}

std::vector<std::vector<bool>> get_subset_matrix(std::vector<ULONG> set, ULONG n, ULONG sum, \
	std::map<int, int>& storing)
{
	std::map<int, int> ways; //sum -> gone thru ...
	// The value of subset[i][j] will be true if there is a
	// subset of set[0..j-1] with sum equal to i
	auto start = std::chrono::steady_clock();
	std::vector<std::vector<bool>> subset(n + 1);
	for (int i = 0; i < n + 1; i++) {
		//this takes ALOTOFTIME!!!
		subset.at(i).resize(sum + 1);
	}

	for (int i = 0; i <= n; i++)
		subset[i][0] = true;

	for (int i = 1; i <= sum; i++)
		subset[0][i] = false;

	// Fill the subset table in bottom up manner
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= sum; j++)
		{
			if (j < set[i - 1]) {
				subset[i][j] = subset[i - 1][j];
			}
			if (j >= set[i - 1]) {
				if (subset[i - 1][j]) {
					subset[i][j] = subset[i - 1][j];
				}
				if (subset[i - 1][j - set[i - 1]]) {
					subset[i][j] = subset[i - 1][j - set[i - 1]];
					ways.insert(std::pair<int, int>(j, set[i - 1]));
				}
			}
		}
	}

	// uncomment this code to print table
	/*for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= sum; j++)
			std::cout << subset[i][j] << " ";
		std::cout << std::endl;
	}*/

	storing = ways;

	return subset;
}

void write_file(std::string filename, std::vector<ULONG> set, std::vector<ULONG> selected)
{
	int numbers_wrote = 0;
	std::fstream outfile(filename, std::ios_base::out);
	outfile << selected.size() << std::endl;
	for (int i = 0; i < set.size(); i++) {
		if (std::find(selected.begin(), selected.end(), set[i]) != selected.end()) {
			outfile << i << " ";
			selected.at(std::distance(selected.begin(), \
				std::find(selected.begin(), selected.end(), set[i]))) = 0;
			numbers_wrote++;
		}
	}

	std::cout << "Writing to " << filename << " done successfully" << std::endl;
	std::cout << "Wrote " << numbers_wrote << std::endl;

	outfile.close();
}

ULONG summed(std::vector<ULONG> arr) {
	ULONG sum = 0;
	return accumulate(arr.begin(), arr.end(), sum);
}