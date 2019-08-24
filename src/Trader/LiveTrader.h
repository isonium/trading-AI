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
	LiveTrader(long double const, Topology_ptr &, State *);
	LiveTrader(Trader & trader);
	~LiveTrader();
};

} /* namespace Trading */

#endif /* TRADER_LIVETRADER_H_ */
