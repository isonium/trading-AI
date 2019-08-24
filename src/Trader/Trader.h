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
#include <memory>

#include "State.h"
#include "../NeuralNetwork/NN.h"
#include "../NeuralNetwork/Topology.h"
#include "../Stock/Stock.h"
#include "../Stock/Portfolio.h"

using namespace NeuralNetwork;

namespace Trading {
struct NotEnoughFunds: public std::exception {
	const char * what() const throw () {
		return "This trader does not have enough funds to buy this stock";
	}
};

class Trader {
public:
	Trader(long double const, Topology_ptr &, State *);
	Trader(Trader & trader);
	virtual ~Trader();

	Trader & operator=(Trader & trader);

	double get_bank() const;

protected:
	State * game_state;
	double bank;
	double assets_value;
	double invested_ratio = 0.0;
	stock::Portfolio * portfolio;
	NeuralNetwork::NN * brain;

	void copy(Trader &);

	virtual void buy_stock(stock::Stock &, const long) = 0;
	virtual void sell_stock(stock::Stock * const, const long) = 0;
};

using Trader_ptr = std::unique_ptr<Trader>;
}

#endif /* TRADER_H_ */
