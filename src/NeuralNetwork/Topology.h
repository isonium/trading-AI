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
#include <memory>
#include <stdlib.h>
#include <iostream>


#include "Phenotype.h"
#include "Mutation.h"
#include "Neuron.h" // Layer

namespace NeuralNetwork {

class Topology {
public:
	Topology() {}
	explicit Topology(Topology const & base);// Private copy constructor
	~Topology() {};

	int get_layers() const;
	std::vector<Phenotype> * get_relationships();

	void set_layers(int const & _layers);
	void add_relationship(Phenotype &, bool);

	bool optimize();
	void new_generation(unsigned const & count, std::vector<std::shared_ptr<Topology>> & new_topologies);


private:

	int layers = 0;
	std::vector<int> layers_size = { };
	std::vector<Phenotype> relationships = { };
	std::vector<Mutation> mutations = { };

	const int * decide_mutation();
	std::shared_ptr<Topology> evolve();
	void mutate();
	void resize(int const & new_size);
};

using Topology_ptr = std::shared_ptr<Topology>;

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_TOPOLOGY_H_ */
