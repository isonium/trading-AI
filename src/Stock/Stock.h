/*
 * Stock.h
 *
 *  Created on: May 10, 2019
 *      Author: sakex
 */

#ifndef STOCK_H_
#define STOCK_H_

#include <iostream>

#include <unordered_map>
#include <vector>
#include <string>

#include <boost/function.hpp>

namespace stock {

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

	typedef std::unordered_map<std::string, std::vector<Position*>*> PositionMap;
}

#endif /* STOCK_H_ */
