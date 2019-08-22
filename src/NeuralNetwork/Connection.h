/*
 * Connection.h
 *
 *  Created on: May 30, 2019
 *      Author: sakex
 */

#ifndef NEURALNETWORK_CONNECTION_H_
#define NEURALNETWORK_CONNECTION_H_

#include "NeuralNetwork.h"
#include "Neuron.h"

namespace NeuralNetwork {

class Neuron;

class Connection{

public:
	Connection(double weight, Neuron * input, Neuron * output);
	~Connection();

	void activate() const;

private:
	double weight;
	Neuron * input;
	Neuron * output;
};

}


#endif /* NEURALNETWORK_CONNECTION_H_ */
