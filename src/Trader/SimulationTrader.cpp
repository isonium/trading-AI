/*
 * SimulationTrader.cpp
 *
 *  Created on: Aug 24, 2019
 *      Author: sakex
 */

#include "SimulationTrader.h"

namespace Trading {

SimulationTrader::SimulationTrader(long double const bank,
		Topology_ptr & brain_topology, State * game_state) :
		Trader(bank, brain_topology, game_state) {
}

SimulationTrader::SimulationTrader(Trader & trader) :
		Trader(trader) {
}

SimulationTrader::~SimulationTrader() {
}

void SimulationTrader::do_reset(Topology_ptr & brain_topology) {
	delete brain;
	delete portfolio;
	this->bank = 100000;
	assets_value = 100000;
	invested_ratio = 0.0;
	brain = new NeuralNetwork::NN(brain_topology);
	portfolio = new stock::Portfolio();
}

double SimulationTrader::do_get_result() const {
	return bank + portfolio->total_value();
}

void SimulationTrader::update_assets() {
	double portfolio_value = portfolio->total_value();
	assets_value = portfolio_value + bank;
	invested_ratio = portfolio_value / assets_value;
}

void SimulationTrader::buy_stock(stock::Stock &_stock, const long quantity) {
	const long double value = _stock.value * quantity;
	if (bank >= value) {
		bank -= value;
		portfolio->add_position(_stock, quantity);
	} else {
		throw NotEnoughFunds();
	}
}

void SimulationTrader::sell_stock(stock::Stock & stock,
		const long quantity) {
	portfolio->remove_stocks(stock.ticker, quantity);
	bank += quantity * stock.value;
}

void SimulationTrader::do_decide() {
	update_assets();
	stock::Candle * candle = game_state->candle;
	stock::Stock * default_stock = game_state->default_stock;
	const double inputs[5] = { candle->open, candle->close, candle->volume,
			candle->timestamp, invested_ratio };
	const double output = brain->compute(inputs);
	rebalance(output, *default_stock);
}

void SimulationTrader::rebalance(const double new_ratio,
		stock::Stock & default_stock) {
	const double delta = new_ratio - invested_ratio;
	const long new_investments = round(delta * (bank + assets_value));
	if (new_investments > 0) {
		buy_stock(default_stock, new_investments);
	} else if (new_investments < 0) {
		sell_stock(default_stock, -1 * new_investments);
	}
}

} /* namespace Trader */
