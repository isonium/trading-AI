/*
 * SimulationTrader.h
 *
 *  Created on: Aug 24, 2019
 *      Author: sakex
 */

#ifndef TRADER_SIMULATIONTRADER_H_
#define TRADER_SIMULATIONTRADER_H_

#include "../Game/Player.h"
#include "Trader.h"

namespace Trading {

class SimulationTrader: public Trader, public Game::Player {
public:
	SimulationTrader(long double const, Topology_ptr &, State *);
	SimulationTrader(Trader &);
	~SimulationTrader();

private:
	void rebalance(const double, stock::Stock &);
	void buy_stock(stock::Stock &, const long);
	void sell_stock(stock::Stock * const, const long);
	void update_assets();

	double do_get_result() const;
	void do_decide();
	void do_reset(Topology_ptr &);
};

using SimulationTrader_ptr = std::unique_ptr<SimulationTrader>;
} /* namespace Trader */

#endif /* TRADER_SIMULATIONTRADER_H_ */
