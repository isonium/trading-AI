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

class Topology {
public:
	size_t get_layers() const;
	std::vector<Phenotype> * get_relationships();

	void set_layers(size_t _layers);
	void add_relationship(Phenotype & phenotype);

private:
	size_t layers;
	std::vector<Phenotype> relationships;
};

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_TOPOLOGY_H_ */
