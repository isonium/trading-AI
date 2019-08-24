/*
 * Mutation.cpp
 *
 *  Created on: Jul 27, 2019
 *      Author: sakex
 */

#include "limits.h"
#include "Mutation.h"

namespace NeuralNetwork {

Mutation::Mutation(Phenotype * _phenotype,
		double const _last_result) {
	phenotype = _phenotype;
	last_result = _last_result;
}

unsigned Mutation::get_iterations() const {
	return iterations;
}

unsigned Mutation::get_unfruitful() const {
	return unfruitful;
}

void Mutation::mutate(double const wealth) {
	const double weight = phenotype->get_weight();
	const double delta = wealth - last_result;
	const int prev_direction = direction;
	if (direction == 0 || direction == 1)
		direction = delta > 0 ? 1 : -1;
	else if (direction == -1)
		direction = delta > 0 ? -1 : 1;
	else
		throw InvalidDirectionException();
	const int index = direction == -1 ? 1 : 0;
	// If direction is -1, then we update the max value of the inverval, else we update the min value
	interval[index] = weight;
	if (prev_direction != direction && prev_direction != 0) {
		// Check direction change
		interval_found = true;
		//interval[1-index] =
	}
	if (!interval_found) {
		++unfruitful;
		phenotype->set_weight(weight + gradient * direction);
		gradient--;
		if (!gradient)
			unfruitful = 1000;
	} else {
		iterations++;
		const double new_weight = (interval[1] + interval[0]) / 2;
		phenotype->set_weight(new_weight);
	}
	if (std::abs(interval[0] - interval[1]) < .5)
		iterations = 1000;
	last_result = wealth;
}

} /* namespace NeuralNetwork */
