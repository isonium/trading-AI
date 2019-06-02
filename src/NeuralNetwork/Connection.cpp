/*
 * Connection.cpp
 *
 *  Created on: May 30, 2019
 *      Author: sakex
 */

#include "Connection.h"

namespace NeuralNetwork {

Connection::Connection(float weight, Neuron * input, Neuron * output){
	this->weight = weight;
	this->input = input;
	this->output = output;
}

} /* namespace NeuralNetwork */
