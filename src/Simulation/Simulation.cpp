/*
 * Simulation.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: sakex
 */

#include "Simulation.h"

const string EVENT_TICK = "tick";

Simulation::Simulation() {
	_stock = {
		"Apple", "AAPL", 0
	};
}

Simulation::~Simulation() {
	// TODO Auto-generated destructor stub
}

void Simulation::on_tick(boost::function<void (stock::Candle *)> function){
	tickEvent.addListener(function);
}

void Simulation::tick() const{
	tickEvent.emit();
}

void Simulation::tick(stock::Candle * c) {
	_stock.value = c->close;
	tickEvent.emit(c);
}


