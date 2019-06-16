#include "Connection.h"



/*
 * Connection.cpp
 *
 *  Created on: May 30, 2019
 *      Author: sakex
 */


namespace NeuralNetwork {

Connection::Connection(float weight, Neuron * input, Neuron * output){
	this->weight = weight;
	this->input = input;
	this->output = output;
}

Connection::~Connection(){
}


float sigmoid(float value){
	return 1/(1 + exp(-value));
}

void Connection::activate() const {
	float input_value = input->get_value();
	output->increment_value(weight * sigmoid(input_value));
}


} /* namespace NeuralNetwork */
