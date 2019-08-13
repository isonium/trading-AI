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
	explicit Topology(Topology const &);// Private copy constructor
	~Topology() {};

	int get_layers() const;
	std::vector<std::shared_ptr<Phenotype>> & get_relationships();

	void set_layers(int const &, int const &);
	void set_layers(int const &);
	void add_relationship(std::shared_ptr<Phenotype> &, bool);

	bool optimize(const double &);
	void new_generation(unsigned const &, std::vector<std::shared_ptr<Topology>> &, double const &);


private:

	int layers = 0;
	std::vector<int> layers_size = { };
	std::vector<std::shared_ptr<Phenotype>> relationships = {};
	std::vector<Mutation> mutations = { };

	void disable_phenotypes();
	const int * decide_mutation();
	std::shared_ptr<Topology> evolve(double const &);
	void mutate();
	void new_mutation(double const & wealth);
	void resize(int const & new_size);
};

using Topology_ptr = std::shared_ptr<Topology>;

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_TOPOLOGY_H_ */
