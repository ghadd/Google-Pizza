#pragma once

#include "Input.h"

Input::Input(ULONG& _max_of_pieces, ULONG& _num_of_variations, std::fstream& file) {
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
    std::vector<std::vector<bool>> subset_matrix = get_subset_matrix(this->slices, this->num_of_variations, this->max_of_pieces);
    ULONG res = this->max_of_pieces;
    while (!subset_matrix[this->num_of_variations][res]) {
        res--;
    }

	return res;
}

std::vector<std::vector<bool>> get_subset_matrix(std::vector<ULONG> set, ULONG n, ULONG sum)
{
    // The value of subset[i][j] will be true if there is a
    // subset of set[0..j-1] with sum equal to i
    std::vector<std::vector<bool>> subset(n + 1);
    for (int i = 0; i < n + 1; i++) {
        subset.at(i).resize(sum + 1);
    }

    // If sum is 0, then answer is true
    for (int i = 0; i <= n; i++)
        subset[i][0] = true;

    // If sum is not 0 and set is empty, then answer is false
    for (int i = 1; i <= sum; i++)
        subset[0][i] = false;

    // Fill the subset table in botton up manner
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            if (j < set[i - 1])
                subset[i][j] = subset[i - 1][j];
            if (j >= set[i - 1])
                subset[i][j] = subset[i - 1][j] ||
                subset[i - 1][j - set[i - 1]];
        }
    }

    // uncomment this code to print table
    /*for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= sum; j++)
            std::cout << subset[i][j] << " ";
        std::cout << std::endl;
    }*/

    return subset;
}