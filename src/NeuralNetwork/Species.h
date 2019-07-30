/*
 * Species.h
 *
 *  Created on: Jul 27, 2019
 *      Author: sakex
 */

#ifndef NEURALNETWORK_SPECIES_H_
#define NEURALNETWORK_SPECIES_H_

#include <vector>
#include "Topology.h"

namespace NeuralNetwork {

class Species {
public:
	Species();
	virtual ~Species();

private:
	std::vector<Topology*> topologies = {};
};

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_SPECIES_H_ */
