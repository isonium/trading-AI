/*
 * Topology.cpp
 *
 *  Created on: July 22, 2019
 *      Author: sakex
 */

#include "Topology.h"

constexpr unsigned MAX_ITERATIONS = 5;
constexpr unsigned MAX_UNFRUITFUL = 3;

namespace NeuralNetwork {
Topology::Topology() {
}

Topology::Topology(nlohmann::json & j) {
	from_json(j);
}

Topology::Topology(Topology const & base) {
	copy(base);
}

Topology::~Topology() {
	for (auto & it : relationships) {
		for (Phenotype * phenotype : it.second) {
			delete phenotype;
		}
	}
}

Topology & Topology::operator=(Topology const & base) {
	if (this != &base) {
		copy(base);
	}

	return *this;
}

void Topology::copy(Topology const & base) {
	layers = base.layers;
	layers_size = base.layers_size;
	mutations = base.mutations;
	for (auto & it : relationships) {
		for (Phenotype * phenotype : it.second) {
			delete phenotype;
		}
	}
	relationships.clear();

	for (auto & it : base.relationships) {
		for (Phenotype * phenotype : it.second) {
			Phenotype * copy = new Phenotype(*phenotype);
			add_to_relationships_map(copy);
		}
	}
}

void Topology::from_json(nlohmann::json & j) {
	for (auto & it : j) {
		Phenotype::point input = { it["input"][0], it["input"][1] };
		Phenotype::point output = { it["output"][0], it["output"][1] };
		double const weight = it["weight"];
		bool disabled = it["disabled"];
		Phenotype * phenotype = new Phenotype(input, output, weight, disabled);
		add_relationship(phenotype);
	}
}

void Topology::set_layers(int const _layers) {
	layers = _layers;
	layers_size.resize(layers, 1);
	layers_size[layers - 1] = layers_size[layers - 2];
	layers_size[layers - 2] = 1;
}

int Topology::get_layers() const {
	return layers;
}

Topology::relationships_map & Topology::get_relationships() {
	return relationships;
}

void Topology::add_relationship(Phenotype * phenotype, const bool init) {
	Phenotype::point input = phenotype->get_input();
	Phenotype::point output = phenotype->get_output();
	if (input[1] + 1 > layers_size[input[0]]) {
		layers_size[input[0]] = input[1] + 1;
	}
	if (!init && output[0] == layers) {
		resize(output[0]);
		phenotype->decrement_output();
	} else if (output[1] + 1 > layers_size[output[0]]) {
		layers_size[output[0]] = output[1] + 1;
	}
	add_to_relationships_map(phenotype);
}

void Topology::add_to_relationships_map(Phenotype * phenotype) {
	Phenotype::point input = phenotype->get_input();
	if (relationships.find(input) != relationships.end()) {
		relationships[input].push_back(phenotype);
	} else {
		relationships[input] = std::vector<Phenotype *> { phenotype };
	}
}

void Topology::disable_phenotypes(Phenotype::point const & input,
		Phenotype::point const & output) {
	if (relationships.find(input) == relationships.end())
		return;
	auto & base_vector = relationships[input];
	Phenotype * & back = base_vector.back();
	for (Phenotype * & it : base_vector) {
		if (it == back || it->is_disabled()) {
			continue;
		}
		Phenotype::point compared_output = it->get_output();
		if (output == compared_output || path_overrides(compared_output, output)
				|| path_overrides(output, compared_output)) {
			it->disable();
		}
	}
}

bool const Topology::path_overrides(Phenotype::point const & input,
		Phenotype::point const & output) {
	if (relationships.find(input) == relationships.end())
		return false;
	auto & base_vector = relationships[input];
	for (Phenotype * & it : base_vector) {
		if (it->is_disabled()) {
			continue;
		}
		Phenotype::point compared_output = it->get_output();
		if (compared_output == output) {
			return true;
		} else if (compared_output[0] <= output[0]) {
			if (path_overrides(compared_output, output))
				return true;
		}
	}
	return false;
}

void Topology::resize(int const new_max) {
	for (auto & it : relationships) {
		for (Phenotype * phenotype : it.second) {
			phenotype->resize(new_max - 1, new_max);
		}
	}
	set_layers(new_max + 1);
}

bool Topology::optimize(const double wealth) {
	if (!mutations.size()) {
		return false;
	}
	Mutation & last_mutation = mutations.back();
	if (last_mutation.get_iterations() >= MAX_ITERATIONS) {
		return false;
	}
	if (last_mutation.get_unfruitful() >= MAX_UNFRUITFUL) {
		return false;
	}
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
	Phenotype * last_phenotype = new_topology->mutate();
	new_topology->new_mutation(last_phenotype, wealth);
	return new_topology;
}

Phenotype * Topology::mutate() {
// Input must already exist and output may or may not exist
	bool new_output = false;
	int input_index = layers >= 3 ? rand() % (layers - 2) : 0;
	int input_position = rand() % (layers_size[input_index]);
	int output_index = rand() % (layers - input_index) + input_index + 1;
	int output_position = 0;
	if (output_index < layers - 1) {
		output_position = rand() % (layers_size[output_index] + 1);
		if (output_position >= layers_size[output_index]) {
			new_output = true;
		}
	} else if (output_index == layers - 1) {
		output_position = rand() % (layers_size[output_index]);
	} else { // if output_index == layers
		new_output = true;
	}
	Phenotype::point input = { input_index, input_position };
	Phenotype::point output = { output_index, output_position };
	Phenotype * last_phenotype = new_phenotype(input, output);

	if (!new_output) {
		int _back = layers_size.back();
		output = last_phenotype->get_output();
		for (int i = 0; i < _back; ++i) {
			Phenotype::point output_output = { layers - 1, i };
			new_phenotype(output, output_output);
		}
	}
	disable_phenotypes(input, output);
	return last_phenotype;
}

Phenotype * Topology::new_phenotype(Phenotype::point const & input,
		Phenotype::point const & output) {
	double weight = (std::rand() % 100) / 100.0;
	Phenotype * phenotype = new Phenotype(input, output, weight);
	add_relationship(phenotype);
	return phenotype;
}

void Topology::new_mutation(Phenotype * last_phenotype, double const wealth) {
	Mutation mutation(last_phenotype, wealth);
	mutations.push_back(mutation);
}

std::string Topology::parse_to_string() const {
	std::string output = "[";
	for (auto & it : relationships) {
		for (Phenotype * phenotype : it.second) {
			output += phenotype->to_string() + ",";
		}
	}
	output.replace(output.end() - 1, output.end(), "]");
	return output;
}
}
