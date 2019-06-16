/*
 * Stock.h
 *
 *  Created on: May 10, 2019
 *      Author: sakex
 */

#ifndef STOCK_H_
#define STOCK_H_

#include <unordered_map>
#include <vector>
#include <string>

#include <boost/function.hpp>

namespace stock{

	typedef struct {
		std::string name;
		std::string ticker;
		long double value;
	} Stock;

	typedef struct {
		const double open;
		const double close;
		const double high;
		const double low;
		const double volume;
		const double timestamp;
	} Candle;

	typedef struct {
		Stock * const stock;
		long quantity;
		const long double initialPrice;
	} Position;

	typedef std::unordered_map<std::string, std::vector<Position*>> PositionMap;

	class Portfolio{
	public:
		Portfolio();
		std::vector<Position*> * find_position(const std::string ticker) const;
		double total_value() const;
		long get_ticker_quantity(const std::string ticker) const;
		void add_position(Position* position);
		void remove_stocks(const std::string ticker, long quantity);

	private:
		PositionMap positions;
	};
}

#endif /* STOCK_H_ */
