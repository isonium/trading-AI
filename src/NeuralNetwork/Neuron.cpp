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

void Neuron::add_connection(Neuron * neuron){
	Connection connection(.1, this, neuron);
	connections.push_back(connection);
}

void Neuron::feed_forward(float input){
	for(Connection connection: connections){
		connection.activate();
	}
}

} /* namespace NeuralNetwork */
