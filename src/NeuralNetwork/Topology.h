/*
 * Topology.h
 *
 *  Created on: Jun 9, 2019
 *      Author: sakex
 */

#ifndef NEURALNETWORK_TOPOLOGY_H_
#define NEURALNETWORK_TOPOLOGY_H_

#include <vector>
#include <queue>
#include <stdexcept>
#include "Mutable.h"
#include "Phenotype.h"
#include "Mutation.h"

namespace NeuralNetwork {

class Topology: public Mutable {
public:
	~Topology(){};

	size_t get_layers() const;
	std::vector<Phenotype> * get_relationships();

	void set_layers(size_t _layers);
	void add_relationship(Phenotype);

	void mutate();

private:
	size_t layers;
	std::vector<Phenotype> relationships = {};
	std::vector<Mutation> mutations = {};

	const int * decide_mutation();
};

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_TOPOLOGY_H_ */
