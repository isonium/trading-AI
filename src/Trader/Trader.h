/*
 * Trader.h
 *
 *  Created on: May 10, 2019
 *      Author: sakex
 */

#include "../Stock/Stock.h"
#include "../Simulation/Simulation.h"

#ifndef TRADER_H_
#define TRADER_H_

class Trader {
public:
	Trader(long double bank, Simulation * simulation);

	virtual ~Trader();

	long double getBank() const;

	void buyStock(stock::Stock * const stockPtr, const int quantity);
	void sellStock(stock::Stock * const stockPtr, const long quantity);

private:
	long double bank;
	stock::Portfolio portfolio;
	Simulation * simulation;
};

#endif /* TRADER_H_ */
