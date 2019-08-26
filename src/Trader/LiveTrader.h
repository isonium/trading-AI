/*
 * LiveTrader.h
 *
 *  Created on: Aug 24, 2019
 *      Author: sakex
 */

#ifndef TRADER_LIVETRADER_H_
#define TRADER_LIVETRADER_H_

#include "Trader.h"

namespace Trading {

class LiveTrader: public Trader {
public:
	LiveTrader(const long double, Topology_ptr &, State *);
	explicit LiveTrader(Trader & trader);
	~LiveTrader();

private:
	void buy_stock(stock::Stock &, const long);
	void sell_stock(stock::Stock &, const long);
};

} /* namespace Trading */

#endif /* TRADER_LIVETRADER_H_ */
