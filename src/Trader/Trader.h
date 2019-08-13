/*
 * Trader.h
 *
 *  Created on: May 10, 2019
 *      Author: sakex
 */

#ifndef TRADER_H_
#define TRADER_H_

#include <boost/bind.hpp>
#include <exception>

#include "../Stock/Stock.h"
#include "../Stock/Portfolio.h"
#include "../Simulation/Simulation.h"
#include "../NeuralNetwork/NN.h"
#include "../NeuralNetwork/Topology.h"

using namespace NeuralNetwork;

struct NotEnoughFunds: public std::exception {
	const char * what() const throw () {
		return "This trader does not have enough funds to buy this stock";
	}
};

class Trader {
public:
	Trader(long double bank, Topology_ptr & brain_topology);
	Trader(Trader & trader);
	virtual ~Trader();

	Trader & operator=(Trader & trader);

	double get_bank() const;
	double get_wealth() const;

	void decide(stock::Candle & candle, stock::Stock & default_stock);
	void reset(long double const & bank, Topology_ptr & brain_topology);

private:
	double bank;
	double assets_value;
	double invested_ratio = 0.0;
	stock::Portfolio * portfolio;
	NeuralNetwork::NN * brain;

	void rebalance(const double &, stock::Stock &default_stock);
	void buy_stock(stock::Stock &_stock, const long & quantity);
	void sell_stock(stock::Stock * const stockPtr, const long & quantity);
	void update_assets();
	void copy(Trader & trader);
};

#endif /* TRADER_H_ */
