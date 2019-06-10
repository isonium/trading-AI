/*
 * NN.h
 *
 *  Created on: May 30, 2019
 *      Author: sakex
 */

#ifndef NEURALNETWORK_NN_H_
#define NEURALNETWORK_NN_H_

#include <iostream>
#include <vector>
#include "Connection.cuh"
#include "Neuron.h"
#include "Topology.h"

namespace NeuralNetwork {

class Neuron;

class NN {
public:
	static std::vector<std::vector<Connection*>> global_layers;
	static std::vector<NN> networks;

	NN(Topology * topology);
	virtual ~NN();


	void set_inputs(std::vector<float>);
	void add_neuron(int layer, int index);
	void connect_neurons(Neuron * input, Neuron * output, int input_layer);

	std::vector<Layer*> get_layers() const;

	Layer * output_layer() const;
private:
	std::vector<Layer*> layers;

	Neuron * get_neuron(int layer, int index) const;
	void init_topology(Topology * topology);

	static void add_to_global(int layer, Connection * connection);
};

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_NN_H_ */
