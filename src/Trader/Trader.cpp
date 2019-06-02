/*
 * Trader.cpp
 *
 *  Created on: May 10, 2019
 *      Author: sakex
 */

#include "Trader.h"

Trader::Trader(long double bank, Simulation * simulation){
	this->bank = bank;
	this->simulation = simulation;
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


void Trader::init_training(){
	simulation->on_tick(boost::bind(&Trader::decide, this, boost::placeholders::_1));
}

void Trader::decide(stock::Candle * c){
	std::cout << c->close << std::endl;
}

