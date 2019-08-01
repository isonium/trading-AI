/*
 * Portfolio.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: sakex
 */

#include "Portfolio.h"

namespace stock {

constexpr long LONG_ZERO = 0;

Portfolio::Portfolio() :
		positions() {
}

Portfolio::~Portfolio() {
	for (auto position_pair : positions) {
		std::vector<Position*> * position_vector = position_pair.second;
		for (Position * position : *position_vector)
			delete position;
		delete position_vector;
	}
}

const std::vector<Position*> * Portfolio::find_position(
		const std::string & ticker) const {
	PositionMap::const_iterator it = positions.find(ticker);
	if (it == positions.end()) {
		// Not found
		return NULL;
	}
	return it->second;
}

void Portfolio::add_position(stock::Stock & _stock, const int quantity) {
	stock::Position * position = new stock::Position { &_stock, quantity,
			_stock.value };
	const std::string ticker = position->stock->ticker;
	std::vector<Position*> * positions_vector =
			const_cast<std::vector<Position*> *>(find_position(ticker));
	if (!positions_vector) {
		std::vector<Position*> * new_vec = new std::vector<Position*>();
		new_vec->push_back(position);
		positions[ticker] = new_vec;
	} else {
		positions_vector->push_back(position);
	}
}

double Portfolio::total_value() const {
	double total = 0;
	for (auto position_map_iterator : positions) {
		total += std::accumulate(position_map_iterator.second->begin(),
				position_map_iterator.second->end(), 0.0,
				[](double total, Position * position) {return total + position->stock->value * position->quantity;});
	}
	return total;
}

long Portfolio::get_ticker_quantity(const std::string & ticker) const {
	std::vector<Position*> * positions_vector =
			const_cast<std::vector<Position*> *>(find_position(ticker));
	if (!positions_vector)
		return 0;
	long total =
			std::accumulate(positions_vector->begin(), positions_vector->end(),
					LONG_ZERO,
					[](long total, Position * position) {return total + position->quantity;});
	return total;
}

void Portfolio::remove_stocks(const std::string & ticker, long quantity) {
	std::vector<Position*> * positions_vector =
			const_cast<std::vector<Position*> *>(find_position(ticker));
	long total_owned = get_ticker_quantity(ticker);
	if (total_owned < quantity)
		throw "This portfolio does not have enough stocks with this ticker";
	while (quantity > 0) {
		Position* first_position_ptr = positions_vector->at(0);
		if (first_position_ptr->quantity > quantity) {
			first_position_ptr->quantity -= quantity;
			break;
		} else {
			quantity -= first_position_ptr->quantity;
			positions_vector->erase(positions_vector->begin());
			delete first_position_ptr;
		}
	}
}

} /* namespace Stock */
