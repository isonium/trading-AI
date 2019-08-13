/*
 * Mutation.cpp
 *
 *  Created on: Jul 27, 2019
 *      Author: sakex
 */

#include "limits.h"
#include "Mutation.h"

namespace NeuralNetwork {

Mutation::Mutation(std::shared_ptr<Phenotype> & _phenotype,
		double const & _last_result) {
	phenotype = _phenotype;
	last_result = _last_result;
}

unsigned const & Mutation::get_iterations() const {
	return iterations;
}

void Mutation::mutate(double const & wealth) {
	const double weight = phenotype->get_weight();
	const double delta = wealth - last_result;
	const int prev_direction = direction;
	if (direction == 0 || direction == 1)
		direction = delta > 0 ? 1 : -1;
	else if (direction == -1)
		direction = delta > 0 ? -1 : 1;
	else
		throw InvalidDirectionException();
	if (prev_direction == 0 || prev_direction == direction) {
		// Direction didn't change
		const int index = direction == -1 ? 1 : 0;
		// If direction is -1, then we update the max value of the inverval, else we update the min value
		interval[index] = weight;
		if (!interval_found) {
			const double growth_delta = std::abs(1 + delta / last_result);
			phenotype->set_weight(weight + direction * growth_delta);
		} else {
			iterations++;
			const double new_weight = (interval[1] + interval[0]) / 2;
			phenotype->set_weight(new_weight);
		}
	} else {
		iterations++;
		interval_found = true;
		const int index = direction == -1 ? 0 : 1;
		interval[index] = weight;
		const double new_weight = (interval[1] + interval[0]) / 2;
		phenotype->set_weight(new_weight);
	}
	last_result = wealth;
}

} /* namespace NeuralNetwork */
