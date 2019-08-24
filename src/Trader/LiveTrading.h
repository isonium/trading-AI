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

namespace Trader {

class LiveTrading {
public:
	LiveTrading(const char * input_file);
	virtual ~LiveTrading();
};

} /* namespace Trader */

#endif /* TRADER_LIVETRADING_H_ */
