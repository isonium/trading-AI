/*
 * Topology.cpp
 *
 *  Created on: July 22, 2019
 *      Author: sakex
 */

#include "Topology.h"

constexpr unsigned MAX_ITERATIONS = 5;

namespace NeuralNetwork {

Topology::Topology(Topology const & base) {
	layers = base.layers;
	layers_size = base.layers_size;
	mutations = base.mutations;
	for (std::shared_ptr<Phenotype> phenotype : base.relationships) {
		relationships.push_back(std::make_shared<Phenotype>(*phenotype));
	}
}

void Topology::set_layers(int const _layers, int const default_count) {
	layers = _layers;
	layers_size.resize(layers, default_count);
}

void Topology::set_layers(int const _layers) {
	set_layers(_layers, 0);
}

int Topology::get_layers() const {
	return layers;
}

std::vector<std::shared_ptr<Phenotype>> & Topology::get_relationships() {
	return relationships;
}

void Topology::add_relationship(std::shared_ptr<Phenotype> & phenotype,
		bool init = false) {
	int * input = phenotype->get_input();
	int * output = phenotype->get_output();
	if (input[1] + 1 > layers_size[input[0]]) {
		layers_size[input[0]] = input[1] + 1;
	}
	if (!init && output[0] > layers - 1) {
		resize(output[0] + 1);
	} else if (output[1] + 1 > layers_size[output[0]]) {
		layers_size[output[0]] = output[1] + 1;
	}
	relationships.push_back(std::move(phenotype));
	disable_phenotypes();
}

void Topology::disable_phenotypes() {
	std::shared_ptr<Phenotype> & last_phenotype = relationships.back();
	for (size_t i = 0; i < relationships.size() - 1; ++i) {
		std::shared_ptr<Phenotype> & compare_phenotype = relationships[i];
		if (compare_phenotype->is_disabled())
			continue;
		if (last_phenotype->overrides(*compare_phenotype)) {
			compare_phenotype->disable();
		}
	}
}

void Topology::resize(int const new_size) {
	for (std::shared_ptr<Phenotype> & phenotype : relationships)
		phenotype->resize(layers, new_size);
	set_layers(new_size, 1);
}

bool Topology::optimize(const double wealth) {
	if (!mutations.size()) {
		return false;
	}
	Mutation & last_mutation = mutations.back();
	if (last_mutation.get_iterations() >= MAX_ITERATIONS)
		return false;
	last_mutation.mutate(wealth);
	return true;
}

void Topology::new_generation(unsigned const count,
		std::vector<Topology_ptr> & topologies, double const wealth) {
	for (unsigned it = 0; it < count; ++it) {
		topologies.emplace_back(evolve(wealth));
	}
}

Topology_ptr Topology::evolve(double const wealth) {
	Topology_ptr new_topology = std::make_shared<Topology>(*this);
	new_topology->mutate();
	new_mutation(wealth);
	return new_topology;
}

void Topology::mutate() {
	// Input must already exist and output may or may not exist
	bool new_output = false;
	int input_index = rand() % (layers - 1);
	int input_position = rand() % (layers_size.at(input_index));
	int output_index = rand() % (layers - input_index) + input_index + 1;
	int output_position = 0;
	if (output_index < layers) {
		output_position = rand() % (layers_size[output_index] + 1);
		if (output_position + 1 > layers_size[output_index]) {
			new_output = true;
		}
	} else {
		new_output = true;
	}
	int input[2] = { input_index, input_position };
	int output[2] = { output_index, output_position };
	float weight = (std::rand() % 100) / 100.0;
	std::shared_ptr<Phenotype> && phenotype = std::make_shared<Phenotype>(input,
			output, weight);
	add_relationship(phenotype);
	if (new_output) {
		int _back = layers_size.back();
		for (int i = 0; i < _back; ++i) {
			float _weight = (std::rand() % 100) / 100.0;
			int output_output[2] = { layers - 1, i };
			std::shared_ptr<Phenotype> && phenotype =
					std::make_shared<Phenotype>(output, output_output, _weight);
			add_relationship(phenotype);
		}
	}
}

void Topology::new_mutation(double const wealth) {
	std::shared_ptr<Phenotype> & phenotype = relationships.back();
	Mutation mutation(phenotype, wealth);
	mutations.push_back(std::move(mutation));
}

std::string Topology::parse_to_string() const {
	std::string output = "[";
	for (std::shared_ptr<Phenotype> phenotype : relationships) {
		output += phenotype->to_string() + ",";
	}
	output += "]";
	return output;
}
}
