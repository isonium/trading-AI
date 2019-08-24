/*
 * NN.cpp
 *
 *  Created on: May 30, 2019
 *      Author: sakex
 */

#include "NN.h"

namespace NeuralNetwork {

NN::NN(Topology_ptr & topology) {
	init_topology(topology);
}

NN::~NN() {
	for (Layer * layer : layers) {
		for (Neuron * neuron : *layer)
			delete neuron;
		delete layer;
	}
}

void NN::init_topology(Topology_ptr & topology) {
	size_t layers_count = topology->get_layers();
	for (size_t it = 0; it < layers_count; ++it) {
		Layer * layer = new Layer();
		layers.push_back(layer);
	}
	Topology::relationships_map & relationships = topology->get_relationships();
	for (auto & it : relationships) {
		for (Phenotype * phenotype : it.second) {
			if (phenotype->is_disabled()) {
				continue;
			}
			Phenotype::point input = phenotype->get_input();
			Phenotype::point output = phenotype->get_output();
			float weight = phenotype->get_weight();
			Neuron * input_neuron_ptr = merge_neuron(input[0], input[1]);
			Neuron * output_neuron_ptr = merge_neuron(output[0], output[1]);
			input_neuron_ptr->add_connection(output_neuron_ptr, weight);
		}
	}
}

Neuron * NN::merge_neuron(size_t const layer, size_t const index) {
	Layer & _layer = *layers[layer];
	if (index < _layer.size()) {
		if (!_layer[index])
			_layer[index] = new Neuron;
		return _layer[index];
	} else {
		Neuron * neuron = new Neuron;
		_layer.resize(index + 1);
		_layer[index] = neuron;
		return neuron;
	}
}

void NN::add_neuron(int const layer, int const index) {
	Neuron * neuron = new Neuron();
	layers[layer]->at(index) = neuron;
}

void NN::connect_neurons(Neuron & input, Neuron & output,
		int const input_layer) {
	input.add_connection(&output);
}

Layer * NN::output_layer() const {
	return layers.back();
}

std::vector<Layer*> NN::get_layers() const {
	return layers;
}

const double NN::compute(const double * inputs_vector) {
	set_inputs(inputs_vector);
	size_t length = layers.size();
	for (size_t it = 0; it < length - 1; ++it) {
		for (Neuron * neuron : *layers[it]) {
			neuron->feed_forward();
		}
	}
	Neuron * neuron = layers[length - 1]->at(0);
	const double value = neuron->get_value();
	neuron->set_value(0);
	return sigmoid(value);
}

void NN::set_inputs(const double * inputs_array) {
	Layer & first_layer = *layers[0];
	size_t length = first_layer.size();
	for (size_t i = 0; i < length; ++i) {
		Neuron * neuron = first_layer[i];
		neuron->set_value(inputs_array[i]);
	}
}

} /* namespace NeuralNetwork */
