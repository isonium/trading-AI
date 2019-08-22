/*
 * Mutation.h
 *
 *  Created on: Jul 27, 2019
 *      Author: sakex
 */

#ifndef NEURALNETWORK_MUTATION_H_
#define NEURALNETWORK_MUTATION_H_

#include <iostream>
#include <memory>
#include <cmath>
#include <exception>

#include "Phenotype.h"

namespace NeuralNetwork {

struct InvalidDirectionException: public std::exception {
	const char * what() const throw () {
		return "Invalid direction";
	}
};

class Mutation {
	/*
	 * Gradient descent first searches for a range between two doubles
	 * Once it found it, it divides the range in two until finding the right value
	 * */
public:
	explicit Mutation(std::shared_ptr<Phenotype> &, double const);
	~Mutation() {
	}
	;

	unsigned get_iterations() const;
	void mutate(const double);

	unsigned get_unfruitful() const;

private:
	std::shared_ptr<Phenotype> phenotype;
	double interval[2] = { -INFINITY, INFINITY };
	bool interval_found = false;
	int direction = 0;
	double last_result = 0;
	unsigned iterations = 0;
	unsigned unfruitful = 0;
	int gradient = 10;
};

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_MUTATION_H_ */
