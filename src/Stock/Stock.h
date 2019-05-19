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

namespace stock{

	typedef struct {
		const std::string name;
		const std::string ticker;
		long double value;
		long double volatility;
	} Stock;

	typedef struct {
		Stock * const stock;
		long quantity;
		const long double initialPrice;
	} Position;

	typedef std::unordered_map<std::string, std::vector<Position*>> PositionMap;

	class Portfolio{
	public:
		Portfolio();
		std::vector<Position*> * findPosition(const std::string ticker) const;
		long getTickerQuantity(const std::string ticker) const;
		void addPosition(Position* position);
		void removeStocks(const std::string ticker, long quantity);

	private:
		PositionMap positions;
	};
}

#endif /* STOCK_H_ */
