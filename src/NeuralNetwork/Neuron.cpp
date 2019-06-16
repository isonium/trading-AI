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
	for(Connection * connection: connections){
		delete connection;
	}
}

Connection * Neuron::add_connection(Neuron * neuron, float weight){
	Connection * connection = new Connection(weight, this, neuron);
	connections.push_back(connection);
	return connection;
}

Connection * Neuron::add_connection(Neuron * neuron){
	return add_connection(neuron, .1);
}

void Neuron::increment_value(const double inc_value){
	value += inc_value;
}

void Neuron::set_value(const double new_value){
	value = new_value;
}

double Neuron::get_value() const {
	return value;
}

void Neuron::feed_forward(){
	for(Connection * connection: connections){
		connection->activate();
	}
	set_value(0);
}

} /* namespace NeuralNetwork */
