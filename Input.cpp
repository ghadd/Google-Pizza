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
	//TODO
	return 0;
}