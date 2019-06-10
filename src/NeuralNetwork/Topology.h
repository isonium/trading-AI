/*
 * Topology.h
 *
 *  Created on: Jun 9, 2019
 *      Author: sakex
 */

#ifndef NEURALNETWORK_TOPOLOGY_H_
#define NEURALNETWORK_TOPOLOGY_H_

#include <vector>
#include <stdexcept>

namespace NeuralNetwork {

typedef struct {
	int input[2];
	int output[2];
	float weight;
} Phenotype;

typedef	struct {
	size_t layers;
	std::vector<Phenotype> relationships;
} Topology;

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_TOPOLOGY_H_ */
