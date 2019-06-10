/*
 * Neuron.cpp
 *
 *  Created on: May 30, 2019
 *      Author: sakex
 */

#include "Neuron.h"

namespace NeuralNetwork {

Neuron::Neuron() {
	value = 0;
}

Neuron::~Neuron() {
	// TODO Auto-generated destructor stub
}

Connection * Neuron::add_connection(Neuron * neuron, float weight){
	Connection connection(weight, this, neuron);
	return &connection;
}

Connection * Neuron::add_connection(Neuron * neuron){
	return add_connection(neuron, .1);
}

void Neuron::increment_value(float inc_value){
	value += inc_value;
}

void Neuron::set_value(float new_value){
	value = new_value;
}

const float Neuron::get_value() const {
	return value;
}

} /* namespace NeuralNetwork */
