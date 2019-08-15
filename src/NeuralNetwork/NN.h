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

#include "Connection.h"
#include "NeuralNetwork.h"
#include "Neuron.h"
#include "Topology.h"

namespace NeuralNetwork {

class Neuron;
class Topology;

class NN {
public:
	explicit NN(Topology_ptr & topology);
	virtual ~NN();

	const double compute(const double *);

	std::vector<Layer*> get_layers() const;

	Layer * output_layer() const;
private:
	std::vector<Layer*> layers;

	Neuron * merge_neuron(int & layer, int & index);

	void add_neuron(int & layer, int & index);
	void connect_neurons(Neuron & input, Neuron & output, int const & input_layer);
	void init_topology(Topology_ptr & topology);
	void set_inputs(const double * inputs_vector);
};

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_NN_H_ */
