/*
 * Train.h
 *
 *  Created on: May 26, 2019
 *      Author: sakex
 */

#ifndef TRAIN_TRAIN_H_
#define TRAIN_TRAIN_H_

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <nlohmann/json.hpp>
#include <unordered_map>

#include "../Simulation/Simulation.h"
#include "../Trader/Trader.h"
#include "../AlpacaServiceHTTP/AlpacaServiceHTTP.h"
#include "../Event/Event.hpp"
#include "../Stock/Stock.h"

using json = nlohmann::json;

class Train {
public:
	Train(int trader_count);
	virtual ~Train();

	void load_data();

private:
	Simulation simulation;
	std::vector<Trader> traders;
	std::vector<stock::Candle> data;

	void parse_data(Response * data);
	void start();
};

#endif /* TRAIN_TRAIN_H_ */
