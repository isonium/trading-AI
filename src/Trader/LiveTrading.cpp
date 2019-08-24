/*
 * LiveTrading.cpp
 *
 *  Created on: Aug 24, 2019
 *      Author: sakex
 */

#include "LiveTrading.h"

namespace Trader {

LiveTrading::LiveTrading(const char * input_file) {
	using json = nlohmann::json;
	std::ifstream file(input_file);
	json::parse(file);

}

LiveTrading::~LiveTrading() {
	// TODO Auto-generated destructor stub
}

} /* namespace Trader */
