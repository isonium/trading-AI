/*
 * Trader.cpp
 *
 *  Created on: May 10, 2019
 *      Author: sakex
 */

#include "Trader.h"

Trader::Trader(long double bank, NeuralNetwork::Topology * brain_topology):
brain(brain_topology){
	this->bank = bank;
}


Trader::~Trader() {
	// TODO Auto-generated destructor stub
}


long double Trader::getBank() const {
	return bank;
}

void Trader::buyStock(stock::Stock * const stockPtr, const int quantity){
	const long double value = stockPtr->value * quantity;
	if(this->bank >= value){
		this->bank -= value;
		stock::Position position {
			stockPtr,
			quantity,
			stockPtr->value
		};
		this->portfolio.addPosition(&position);
	}
	else{
		throw "This trader does not have enough funds to buy this stock";
	}
}

void Trader::sellStock(stock::Stock * const stockPtr, const long quantity){
	portfolio.removeStocks(stockPtr->ticker, quantity);
	bank += quantity * stockPtr->value;
}

void Trader::decide(){
	std::cout << "decide" << std::endl;
	std::cout << brain.get_layers().at(0)->at(0)->value << std::endl;
}

