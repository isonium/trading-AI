/*
 * Connection.h
 *
 *  Created on: May 30, 2019
 *      Author: sakex
 */

#ifndef NEURALNETWORK_CONNECTION_CUH_
#define NEURALNETWORK_CONNECTION_CUH_

#include <math.h>
#include "Neuron.h"

namespace NeuralNetwork {

struct Neuron;

struct Connection{

public:
	Connection(float weight, Neuron * input, Neuron * output);
	~Connection();

	float weight;
	Neuron * input;
	Neuron * output;
};

}


#endif /* NEURALNETWORK_CONNECTION_H_ */
