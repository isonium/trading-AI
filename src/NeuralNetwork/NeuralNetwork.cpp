/*
 * NeuralNetwork.cpp
 *
 *  Created on: Aug 15, 2019
 *      Author: sakex
 */

#include "NeuralNetwork.h"

namespace NeuralNetwork {

double sigmoid(double const & value) {
	return 1/(1 + std::exp(-value));
}

} /* namespace NeuralNetwork */
