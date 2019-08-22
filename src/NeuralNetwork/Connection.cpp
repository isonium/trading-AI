#include "Connection.h"



/*
 * Connection.cpp
 *
 *  Created on: May 30, 2019
 *      Author: sakex
 */


namespace NeuralNetwork {

Connection::Connection(double weight, Neuron * input, Neuron * output){
	this->weight = weight;
	this->input = input;
	this->output = output;
}

Connection::~Connection(){
}

void Connection::activate() const {
	const double input_value = input->get_value();
	output->increment_value(weight * sigmoid(input_value));
}


} /* namespace NeuralNetwork */
