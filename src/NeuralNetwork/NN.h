/*
 * NN.h
 *
 *  Created on: May 30, 2019
 *      Author: sakex
 */

#ifndef NEURALNETWORK_NN_H_
#define NEURALNETWORK_NN_H_

#include <vector>

#include "Neuron.h"

namespace NeuralNetwork {

class NN {
public:
	NN();
	virtual ~NN();

private:
	std::vector<Layer> layers;
};

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_NN_H_ */
