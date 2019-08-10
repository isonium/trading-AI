/*
 * Trader.cpp
 *
 *  Created on: May 10, 2019
 *      Author: sakex
 */

#include "Trader.h"

Trader::Trader(long double bank, Topology_ptr & brain_topology) {
	this->brain = new NeuralNetwork::NN(brain_topology);
	this->portfolio = new stock::Portfolio();
	this->bank = bank;
	this->assets_value = bank;
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

void Trader::reset(long double bank, Topology_ptr & brain_topology) {
	delete brain;
	delete portfolio;
	this->bank = bank;
	assets_value = bank;
	invested_ratio = 0.0;
	brain = new NeuralNetwork::NN(brain_topology);
	portfolio = new stock::Portfolio();
}

double Trader::get_bank() const {
	return bank;
}

double Trader::get_wealth() const {
	return bank + portfolio->total_value();
}

void Trader::update_assets() {
	double portfolio_value = portfolio->total_value();
	assets_value = portfolio_value + bank;
	invested_ratio = portfolio_value / assets_value;
}

void Trader::buy_stock(stock::Stock &_stock, const int quantity) {
	const long double value = _stock.value * quantity;
	if (bank >= value) {
		bank -= value;
		portfolio->add_position(_stock, quantity);
	} else {
		throw "This trader does not have enough funds to buy this stock";
	}
}

void Trader::sell_stock(stock::Stock * const stockPtr, const long quantity) {
	portfolio->remove_stocks(stockPtr->ticker, quantity);
	bank += quantity * stockPtr->value;
}

void Trader::decide(stock::Candle & candle, stock::Stock & default_stock) {
	update_assets();
	const double inputs[5] = { candle.open, candle.close, candle.volume,
			candle.timestamp, invested_ratio };
	const double output = brain->compute(inputs);
	rebalance(output, default_stock);
}

void Trader::rebalance(const double new_ratio, stock::Stock &default_stock) {
	const double delta = new_ratio - invested_ratio;
	const long new_investments = round(delta * (bank + assets_value));
	if (new_investments > 0) {
		buy_stock(default_stock, new_investments);
	} else if (new_investments < 0) {
		sell_stock(&default_stock, -1 * new_investments);
	}
	// If 0 don't do anything
}

