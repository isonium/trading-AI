/*
 * LiveTrading.cpp
 *
 *  Created on: Aug 24, 2019
 *      Author: sakex
 */

#include "LiveTrading.h"

namespace Trading {

LiveTrading::LiveTrading(Topology_ptr topology) :
		trader(100000.0, topology, state) {
}

LiveTrading::~LiveTrading() {
}

} /* namespace Trader */
