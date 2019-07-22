/*
 * Trader.cpp
 *
 *  Created on: May 10, 2019
 *      Author: sakex
 */

#include "Trader.h"

Trader::Trader(long double bank, NeuralNetwork::Topology * brain_topology):
brain(brain_topology)
{
	this->bank = bank;
	this->assets_value = bank;
}


Trader::~Trader() {
	// TODO Auto-generated destructor stub
}


double Trader::get_bank() const {
	return bank;
}

void Trader::update_assets(){
	double portfolio_value = portfolio.total_value();
	assets_value = portfolio_value + bank;
	invested_ratio = portfolio_value / assets_value;
}

void Trader::buy_stock(stock::Stock &_stock, const int quantity){
	const long double value = _stock.value * quantity;
	if(bank >= value){
		bank -= value;
		stock::Position * position = new stock::Position {
			&_stock,
			quantity,
			_stock.value
		};
		portfolio.add_position(position);
	}
	else{
		throw "This trader does not have enough funds to buy this stock";
	}
}

void Trader::sell_stock(stock::Stock * const stockPtr, const long quantity){
	portfolio.remove_stocks(stockPtr->ticker, quantity);
	bank += quantity * stockPtr->value;
}

void Trader::decide(stock::Candle &candle, stock::Stock &default_stock){
	update_assets();
	const double inputs[] = {
			candle.open,
			candle.close,
			candle.volume,
			candle.timestamp,
			invested_ratio
	};
	const double output = brain.compute(inputs);
	rebalance(output, default_stock);
}

void Trader::rebalance(const double new_ratio, stock::Stock &default_stock){
	const double delta = new_ratio - invested_ratio;
	const long new_investments = round(delta * (bank + assets_value));
	if(new_investments > 0){
		buy_stock(default_stock, new_investments);
	}
	else if(new_investments < 0){
		sell_stock(&default_stock, -1 * new_investments);
	}
	// If 0 don't do anything
}

