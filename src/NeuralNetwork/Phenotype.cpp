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
}

void Phenotype::update_weight(float gradient) {
	weight *= gradient;
}

void Phenotype::set_output(int first, int second) {
	output[0] = first;
	output[1] = second;
}

int * Phenotype::get_input() {
	return input;
}

int * Phenotype::get_output() {
	return output;
}

float Phenotype::get_weight() const {
	return weight;
}

}