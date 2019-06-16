/*
 * NN.cpp
 *
 *  Created on: May 30, 2019
 *      Author: sakex
 */

#include "NN.h"

namespace NeuralNetwork {

NN::NN(Topology * topology): layers() {
	init_topology(topology);
}

NN::~NN() {
	for(Layer * layer: layers){
		for(Neuron * neuron: *layer) delete neuron;
		delete layer;
	}
}

void NN::init_topology(Topology * topology){
	size_t layers_count = topology->layers;
	for(size_t it = 0; it < layers_count; ++it){
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
		input_neuron_ptr->add_connection(output_neuron_ptr, weight);
	}
	output_layer();
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

void NN::add_neuron(int layer, int index){
	Neuron * neuron = new Neuron();
	layers[layer]->at(index) = neuron;
}

void NN::connect_neurons(Neuron * input, Neuron * output, int input_layer){
	input->add_connection(output);
}

Layer * NN::output_layer() const {
	return layers.back();
}

std::vector<Layer*> NN::get_layers() const {
	return layers;
}
const double NN::compute(const double * inputs_vector){
	set_inputs(inputs_vector);
	size_t length = layers.size();
	for(size_t it = 0; it < length - 1; ++it){
		for(Neuron * neuron: *layers[it]){
			neuron->feed_forward();
		}
	}
	Neuron * neuron = layers[length - 1]->at(0);
	const double value = neuron->get_value();
	neuron->set_value(0);
	return value;
}

void NN::set_inputs(const double * inputs_vector){
	size_t length = layers[0]->size();
	for(size_t i = 0; i < length; ++i){
		layers[0]->at(i)->set_value(inputs_vector[i]);
	}
}

} /* namespace NeuralNetwork */
