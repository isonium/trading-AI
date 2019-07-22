/*
 * Topology.cpp
 *
 *  Created on: July 22, 2019
 *      Author: sakex
 */


#include "Topology.h"

namespace NeuralNetwork {
	size_t Topology::get_layers() const {
		return layers;
	}

	std::vector<Phenotype>* Topology::get_relationships() {
		std::vector<Phenotype> * relationships_pointer = &relationships;
		return relationships_pointer;
	}

	void Topology::add_relationship(Phenotype & phenotype) {
		relationships.push_back(phenotype);
	}

	void Topology::set_layers(size_t _layers) {
		layers = _layers;
	}
}
