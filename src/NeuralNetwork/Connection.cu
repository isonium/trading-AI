#include "Connection.cuh"



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


} /* namespace NeuralNetwork */
