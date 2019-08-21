/*
 * Phenotype.cpp
 *
 *  Created on: Jul 28, 2019
 *      Author: sakex
 */

#include "Phenotype.h"

namespace NeuralNetwork {

Phenotype::Phenotype(int input[2], float weight) {
	this->input[0] = input[0];
	this->input[1] = input[1];
	this->weight = weight;
	this->disabled = false;
}

Phenotype::Phenotype(int input[2], int output[2], float weight) {
	this->input[0] = input[0];
	this->input[1] = input[1];
	this->output[0] = output[0];
	this->output[1] = output[1];
	this->weight = weight;
	this->disabled = false;
}

void Phenotype::set_weight(float const new_weight) {
	weight = new_weight;
}

void Phenotype::set_output(int const first, int const second) {
	output[0] = first;
	output[1] = second;
}

int * Phenotype::get_input() {
	return input;
}

int * Phenotype::get_output() {
	return output;
}

double Phenotype::get_weight() const {
	return weight;
}

void Phenotype::disable() {
	disabled = true;
}

bool Phenotype::is_disabled() const {
	return disabled;
}

void Phenotype::resize(int const former_size, int const new_size) {
	if (output[0] == former_size)
		output[0] = new_size;
}

bool Phenotype::overrides(Phenotype const & comparison) const {
	bool input_compare = input[0] == comparison.input[0]
			&& input[1] == comparison.input[1];
	bool output_compare = output[0] == comparison.output[0]
			&& output[1] == comparison.output[1];
	if (input_compare && output_compare) {
		return true;
	}
	return false;
}

std::string Phenotype::parse_to_string() const {
	std::string str = "{\"input\":[" + std::to_string(input[0]) + ","
			+ std::to_string(input[1]) + "], \"output\":["
			+ std::to_string(output[0]) + "," + std::to_string(output[1])
			+ "],\"weight\":" + std::to_string(weight) + ",\"disabled\":"
			+ (disabled ? "true" : "false") + "}";
	return str;
}
}
