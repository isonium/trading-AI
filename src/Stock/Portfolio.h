/*
 * Portfolio.h
 *
 *  Created on: Jul 31, 2019
 *      Author: sakex
 */

#ifndef STOCK_PORTFOLIO_H_
#define STOCK_PORTFOLIO_H_

#include <vector>
#include <numeric>
#include <exception>

#include "Stock.h"

namespace stock {

class NoTickerException: public std::exception {
	const char * what() const throw() {
		return "This portfolio does not have enough stocks with this ticker";
	}
};

class Portfolio {
public:
	Portfolio();
	~Portfolio();
	const std::vector<Position*> * find_position(const std::string & ticker) const;
	double total_value() const;
	long get_ticker_quantity(const std::string & ticker) const;
	void add_position(stock::Stock & _stock, const int quantity);
	void remove_stocks(const std::string & ticker, long quantity);

private:
	PositionMap positions;
};

} /* namespace Stock */

#endif /* STOCK_PORTFOLIO_H_ */
