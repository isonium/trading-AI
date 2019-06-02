/*
 * Neuron.h
 *
 *  Created on: May 30, 2019
 *      Author: sakex
 */

#ifndef NEURALNETWORK_NEURON_H_
#define NEURALNETWORK_NEURON_H_

#include <vector>

#include "Connection.h"

namespace NeuralNetwork {

struct Connection;


class Neuron {
public:
	Neuron();
	virtual ~Neuron();

	void add_connection(Neuron*);
	void feed_forward(float input);

private:
	std::vector<Connection> connections;
	long double value;
};



typedef std::vector<Neuron> Layer;

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_NEURON_H_ */
