/*

 * Neuron.h
 *
 *  Created on: May 30, 2019
 *      Author: sakex
 */

#ifndef NEURALNETWORK_NEURON_H_
#define NEURALNETWORK_NEURON_H_

#include <vector>
#include <iostream>


#include "Connection.cuh"

namespace NeuralNetwork {

struct Connection;


struct Neuron {
public:
	Neuron();
	virtual ~Neuron();

	Connection * add_connection(Neuron * neuron, float weight);
	Connection * add_connection(Neuron*);

	void increment_value(float inc_value);
	void set_value(float new_value);

	const float get_value() const;

	float value;
};



typedef std::vector<Neuron *> Layer;

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_NEURON_H_ */
