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
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "Mutation.h"
#include "Neuron.h" // Layer

#include "../Serializer/Serializer.h"

namespace NeuralNetwork {

class Topology: public Serializer::Serializable {
public:
	using relationships_map = std::unordered_map<Phenotype::point, std::vector<Phenotype *>>;

	Topology();
	explicit Topology(nlohmann::json &);
	explicit Topology(Topology const &); // Private copy constructor
	~Topology();
	Topology & operator=(Topology const &);

	int get_layers() const;
	relationships_map & get_relationships();

	void set_layers(int const);
	void add_relationship(Phenotype *, const bool init = false);

	bool optimize(const double);
	void new_generation(unsigned const,
			std::vector<std::shared_ptr<Topology>> &, double const);

private:
	using point_pair = std::array<Phenotype::point, 2>;

	int layers = 0;
	std::vector<int> layers_size = { };
	relationships_map relationships = { };
	std::vector<Mutation> mutations = { };

	void copy(Topology const & base);
	void from_json(nlohmann::json &);

	void add_to_relationships_map(Phenotype * phenotype);
	void disable_phenotypes(Phenotype::point const &, Phenotype::point const &);
	bool const path_overrides(Phenotype::point const &,
			Phenotype::point const &);
	void resize(int const new_size);

	std::shared_ptr<Topology> evolve(double const);
	Phenotype * mutate();
	void new_mutation(Phenotype *, double const wealth);


	Phenotype * new_phenotype(Phenotype::point const & input,
			Phenotype::point const & output);

	std::string parse_to_string() const;
};

using Topology_ptr = std::shared_ptr<Topology>;

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_TOPOLOGY_H_ */
