/*
 * Mutation.cpp
 *
 *  Created on: Jul 27, 2019
 *      Author: sakex
 */

#include "limits.h"
#include "Mutation.h"

namespace NeuralNetwork {

Mutation::Mutation(Phenotype * _phenotype) {
	phenotype = _phenotype;
}

unsigned const & Mutation::get_iterations() const {
	if(gradient >= .9 && gradient <= 1.1){
		return UINT_MAX;
	}
	return iterations;
}

void Mutation::mutate(){
	iterations++;
	phenotype->update_weight(gradient);
}

} /* namespace NeuralNetwork */
