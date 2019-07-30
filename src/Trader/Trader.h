/*
 * Trader.h
 *
 *  Created on: May 10, 2019
 *      Author: sakex
 */

#ifndef TRADER_H_
#define TRADER_H_

#include <boost/bind.hpp>

#include "../Stock/Stock.h"
#include "../Simulation/Simulation.h"
#include "../NeuralNetwork/NN.h"
#include "../NeuralNetwork/Topology.h"

class Trader {
public:
	Trader(long double bank, NeuralNetwork::Topology *brain_topology);

	virtual ~Trader();

	double get_bank() const;
	double get_wealth() const;

	void update_assets();
	void buy_stock(stock::Stock &_stock, const int quantity);
	void sell_stock(stock::Stock * const stockPtr, const long quantity);
	void decide(stock::Candle &candle, stock::Stock &default_stock);
	void rebalance(const double, stock::Stock &default_stock);

private:
	double bank;
	double assets_value;
	double invested_ratio = 0.0;
	stock::Portfolio portfolio;

	NeuralNetwork::NN * brain;

	void init_traders();
};

#endif /* TRADER_H_ */
