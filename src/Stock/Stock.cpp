/*
 * Stock.cpp
 *
 *  Created on: May 10, 2019
 *      Author: sakex
 */

#include "Stock.h"

using namespace stock;

Portfolio::Portfolio(){
	this->positions = PositionMap();
}

std::vector<Position*> * Portfolio::findPosition(const std::string ticker) const{
	PositionMap::const_iterator it = positions.find(ticker);
	if(it == positions.end()){
		// Not found
		return NULL;
	}
	return const_cast<std::vector<Position*>*>(&(it->second));
}

void Portfolio::addPosition(Position* position){
	const std::string ticker = position->stock->ticker;
	std::vector<Position*> * positionsVector = findPosition(ticker);
	if(!positionsVector){
		positionsVector->push_back(position);
	}
	else{
		positions[ticker] = {position};
	}
}

long Portfolio::getTickerQuantity(const std::string ticker) const {
	std::vector<Position*> * positionsVector = findPosition(ticker);
	if(!positionsVector) return 0;
	long total = 0;
	std::vector<Position*>::iterator position;
	for(position = positionsVector->begin(); position != positionsVector->end() ; ++position){
		total += (*position)->quantity;
	}
	return total;
}


void Portfolio::removeStocks(const std::string ticker, long quantity){
	std::vector<Position*> * positionsVector = findPosition(ticker);
	long totalOwned = getTickerQuantity(ticker);
	if(totalOwned > quantity) throw "This portfolio does not have enough stocks with this ticker";
	Position* firstPositionPtr;
	while(quantity > 0){
		firstPositionPtr = positionsVector->at(0);
		if(firstPositionPtr->quantity > quantity){
			firstPositionPtr->quantity -= quantity;
			break;
		}
		else{
			quantity -= firstPositionPtr->quantity;
			positionsVector->erase(positionsVector->begin());
			delete firstPositionPtr;
		}
	}
}
