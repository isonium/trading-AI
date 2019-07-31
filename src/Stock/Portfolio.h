/*
 * Portfolio.h
 *
 *  Created on: Jul 31, 2019
 *      Author: sakex
 */

#ifndef STOCK_PORTFOLIO_H_
#define STOCK_PORTFOLIO_H_

#include <vector>
#include "Stock.h"

namespace stock {

class Portfolio {
public:
	Portfolio();
	~Portfolio();
	const std::vector<Position*> * find_position(const std::string ticker) const;
	double total_value() const;
	long get_ticker_quantity(const std::string ticker) const;
	void add_position(stock::Position * position);
	void remove_stocks(const std::string ticker, long quantity);

private:
	PositionMap positions;
};

} /* namespace Stock */

#endif /* STOCK_PORTFOLIO_H_ */
