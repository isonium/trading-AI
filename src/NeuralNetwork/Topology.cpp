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
	relationships = base.relationships;
	mutations = base.mutations;
}

void Topology::set_layers(int const & _layers) {
	layers = _layers;
	layers_size.resize(layers, 0);
}

int Topology::get_layers() const {
	return layers;
}

std::vector<Phenotype> * Topology::get_relationships() {
	std::vector<Phenotype> * relationships_pointer = &relationships;
	return relationships_pointer;
}

void Topology::add_relationship(Phenotype & phenotype, bool init = false) {
	int * input = phenotype.get_input();
	int * output = phenotype.get_output();
	if (input[1] + 1 > layers_size[input[0]]) {
		layers_size[input[0]] = input[1] + 1;
	}
	if (!init && output[0] > layers - 1) {
		resize(output[0] + 1);
	}
	else if (output[1] + 1 > layers_size[output[0]]) {
		layers_size[output[0]] = output[1] + 1;
	}
	relationships.push_back(phenotype);
}

void Topology::resize(int const & new_size) {
	for (Phenotype phenotype : relationships)
		phenotype.resize(layers, new_size);
	set_layers(new_size);
}

bool Topology::optimize() {
	if (!mutations.size()) {
		return false;
	}
	Mutation last_mutation = mutations.back();
	std::cout << 1 << std::endl;
	if (last_mutation.get_iterations() >= MAX_ITERATIONS)
		return false;
	last_mutation.mutate();
	return true;
}

void Topology::new_generation(unsigned const & count,
		std::vector<Topology_ptr> & topologies) {
	for (unsigned it = 0; it < count; ++it) {
		topologies.emplace_back(evolve());
	}
}

Topology_ptr Topology::evolve() {
	Topology_ptr new_topology = std::make_shared<Topology>(*this);
	new_topology->mutate();
	return new_topology;
}

void Topology::mutate() {
	// Input must already exist and output may or may not exist
	int input_index = rand() % (layers - 1) + 1;
	int input_position = rand() % (layers_size.at(input_index)) + 1;
	int output_index = rand() % (layers - input_index) + input_index;
	int output_position = 0;
	if (output_index < layers - 1) {
		output_position = rand() % (layers_size.at(output_index)) + 1;
	}
	int input[2] = { input_index, input_position };
	int output[2] = { output_index, output_position };
	Phenotype phenotype(input, output, .5);
	add_relationship(phenotype);
}
}
