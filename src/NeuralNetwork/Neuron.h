/*

 * Neuron.h
 *
 *  Created on: May 30, 2019
 *      Author: sakex
 */

#ifndef NEURALNETWORK_NEURON_H_
#define NEURALNETWORK_NEURON_H_

#include <vector>
#include <iostream>


#include "Connection.h"

namespace NeuralNetwork {

class Connection;


class Neuron {
public:
	Neuron();
	virtual ~Neuron();

	Connection * add_connection(Neuron * neuron, float weight);
	Connection * add_connection(Neuron*);

	void increment_value(const double inc_value);
	void set_value(const double new_value);

	double get_value() const;
	void feed_forward();

private:
	double value;
	std::vector<Connection*> connections;
};



typedef std::vector<Neuron *> Layer;

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_NEURON_H_ */
