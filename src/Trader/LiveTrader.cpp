/*
 * LiveTrader.cpp
 *
 *  Created on: Aug 24, 2019
 *      Author: sakex
 */

#include "LiveTrader.h"

namespace Trading {

LiveTrader::LiveTrader(long double const bank,
		Topology_ptr & brain_topology, State * game_state) :
		Trader(bank, brain_topology, game_state) {
}

LiveTrader::LiveTrader(Trader & trader) :
		Trader(trader) {
}

LiveTrader::~LiveTrader() {
}

} /* namespace Trading */
