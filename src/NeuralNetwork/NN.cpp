/*
 * NN.cpp
 *
 *  Created on: May 30, 2019
 *      Author: sakex
 */

#include "NN.h"

namespace NeuralNetwork {

std::vector<std::vector<Connection*>> NN::global_layers;
std::vector<NN> NN::networks;

NN::NN(Topology * topology): layers() {
	networks.push_back(*this);
	init_topology(topology);
}

NN::~NN() {
	for(Layer * layer: layers){
		delete layer;
	}
}

void NN::init_topology(Topology * topology){
	size_t layers_count = topology->layers;
	for(int it = 0; it < layers_count; ++it){
		Layer * layer = new Layer();
		layers.push_back(layer);
	}
	std::vector<Phenotype> relationships = topology->relationships;
	for(Phenotype phenotype: relationships){
		int input_layer = phenotype.input[0];
		int input_index = phenotype.input[1];
		int output_layer = phenotype.output[0];
		int output_index = phenotype.output[1];
		float weight = phenotype.weight;
		Neuron * input_neuron_ptr = get_neuron(input_layer, input_index);
		Neuron * output_neuron_ptr = get_neuron(output_layer, output_index);
		Connection * connection = input_neuron_ptr->add_connection(output_neuron_ptr, weight);
		add_to_global(input_layer, connection);
	}
	output_layer();
}

void NN::add_to_global(int layer, Connection * connection){
	try{
		std::vector<Connection*> &_layer = global_layers.at(layer);
		_layer.push_back(connection);
	}
	catch (const std::out_of_range& oor){
		global_layers.resize(layer+1);
		global_layers[layer].push_back(connection);
	}
}

Neuron * NN::get_neuron(int layer, int index) const {
	try{
		Neuron * neuron = layers[layer]->at(index);
		if (!neuron) throw std::out_of_range("Not defined");
		return neuron;
	}
	catch (const std::out_of_range& oor){
		Neuron * neuron = new Neuron();
		Layer *_layer = layers[layer];
		_layer->resize(index+1);
		_layer->at(index) = neuron;
		return neuron;
	}
}

void NN::set_inputs(std::vector<float> inputs_vector){
	size_t length = inputs_vector.size();
	for(size_t i = 0; i < length; ++i){
		layers[0]->at(i)->set_value(inputs_vector[i]);
	}
}

void NN::add_neuron(int layer, int index){
	Neuron * neuron;
	layers[layer]->at(index) = neuron;
}

void NN::connect_neurons(Neuron * input, Neuron * output, int input_layer){
	Connection * connection = input->add_connection(output);
	global_layers[input_layer-1].push_back(connection);
}

Layer * NN::output_layer() const {
	return layers.back();
}

std::vector<Layer*> NN::get_layers() const {
	return layers;
}

} /* namespace NeuralNetwork */
