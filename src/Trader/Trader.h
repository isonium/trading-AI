/*
 * Trader.h
 *
 *  Created on: May 10, 2019
 *      Author: sakex
 */


#include <boost/bind.hpp>

#include "../Stock/Stock.h"
#include "../Simulation/Simulation.h"
#include "../NeuralNetwork/NN.h"
#include "../NeuralNetwork/Topology.h"

#ifndef TRADER_H_
#define TRADER_H_

class Trader {
public:
	Trader(long double bank, NeuralNetwork::Topology *brain_topology);

	virtual ~Trader();

	long double getBank() const;

	void buyStock(stock::Stock * const stockPtr, const int quantity);
	void sellStock(stock::Stock * const stockPtr, const long quantity);
	void decide();

private:
	long double bank;
	stock::Portfolio portfolio;

	NeuralNetwork::NN brain;

	void init_traders();
};

#endif /* TRADER_H_ */
