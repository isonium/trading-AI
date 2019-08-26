/*
 * LiveTrading.h
 *
 *  Created on: Aug 24, 2019
 *      Author: sakex
 */

#ifndef TRADER_LIVETRADING_H_
#define TRADER_LIVETRADING_H_

#include <fstream>
#include <nlohmann/json.hpp>
#include "State.h"
#include "LiveTrader.h"
#include "../NeuralNetwork/Topology.h"

namespace Trading {

class LiveTrading {
public:
	LiveTrading(Topology_ptr topology);
	virtual ~LiveTrading();

private:
	State * state = NULL;
	LiveTrader trader;
};

} /* namespace Trader */

#endif /* TRADER_LIVETRADING_H_ */
