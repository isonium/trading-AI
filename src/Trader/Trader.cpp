/*
 * Trader.cpp
 *
 *  Created on: May 10, 2019
 *      Author: sakex
 */

#include "Trader.h"

namespace Trading {

Trader::Trader(long double const bank, Topology_ptr & brain_topology,
		State * game_state) {
	this->brain = new NeuralNetwork::NN(brain_topology);
	this->portfolio = new stock::Portfolio();
	this->bank = bank;
	this->assets_value = bank;
	this->game_state = game_state;
}

Trader::Trader(Trader & trader) {
	copy(trader);
}

Trader::~Trader() {
	delete brain;
	delete portfolio;
}

Trader & Trader::operator=(Trader & trader) {
	copy(trader);
	return *this;
}

void Trader::copy(Trader & trader) {
	bank = trader.bank;
	assets_value = trader.assets_value;
	invested_ratio = trader.invested_ratio;
	delete portfolio;
	delete brain;
	portfolio = new stock::Portfolio(*trader.portfolio);
	brain = new NN(*trader.brain);
}

double Trader::get_bank() const {
	return bank;
}

}
