/*
 * State.h
 *
 *  Created on: Aug 14, 2019
 *      Author: sakex
 */

#ifndef TRADER_STATE_H_
#define TRADER_STATE_H_

#include "../Stock/Stock.h"

namespace Trading {
struct State {
	stock::Candle * candle;
	stock::Stock * default_stock;
};
}

#endif /* TRADER_STATE_H_ */
