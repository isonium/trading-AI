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
#include <vector>
#include <memory>
#include <algorithm>
#include <chrono>

#include "structures.h"
#include "../Simulation/Simulation.h"
#include "../Trader/Trader.h"
#include "../AlpacaServiceHTTP/AlpacaServiceHTTP.h"
#include "../Event/Event.hpp"
#include "../Stock/Stock.h"
#include "../NeuralNetwork/Topology.h"
#include "../NeuralNetwork/NN.h"
#include "../Threading/ThreadPool.h"

namespace Train {
using json = nlohmann::json;
using namespace NeuralNetwork;

class Train {
public:
	Train(int const & initial_topology_count, int const & inputs, int const & outputs);
	~Train();

	void load_data();

private:
	Simulation simulation;
	std::vector<std::shared_ptr<Trader>> traders;
	std::vector<stock::Candle> data;
	std::vector<Topology_ptr> topologies;
	stock::Stock * default_stock;

	void parse_data(Response * res);
	void start();
	void init_traders();
	void reset_traders();
	void run_dataset();
	void natural_selection();
};
}

#endif /* TRAIN_TRAIN_H_ */
