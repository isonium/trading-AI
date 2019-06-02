/*
 * Simulation.h
 *
 *  Created on: Apr 6, 2019
 *      Author: sakex
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include <iostream>

#include "../Event/Event.hpp"
#include "../Stock/Stock.h"

class Simulation {
public:
	Simulation();
	virtual ~Simulation();

	void tick() const;
	void tick(stock::Candle * c);
	void on_tick(boost::function<void (stock::Candle *)>);

private:
	Event<stock::Candle *> tickEvent;
	stock::Stock _stock;
};

#endif /* SIMULATION_H_ */
