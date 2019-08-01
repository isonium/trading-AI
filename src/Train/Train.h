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

#include "structures.h"
#include "../Simulation/Simulation.h"
#include "../Trader/Trader.h"
#include "../AlpacaServiceHTTP/AlpacaServiceHTTP.h"
#include "../Event/Event.hpp"
#include "../Stock/Stock.h"
#include "../NeuralNetwork/Topology.h"
#include "../NeuralNetwork/NN.h"

namespace Train {
using json = nlohmann::json;

class Train {
public:
	Train(int initial_topology_count, int inputs, int outputs);
	~Train();

	void load_data();

private:
	Simulation simulation;
	std::vector<std::shared_ptr<Trader>> traders;
	std::vector<stock::Candle> data;
	std::vector<NeuralNetwork::Topology> topologies;

	void parse_data(Response * data);
	void start();
	void init_traders();
	void reset_traders();
	void run_dataset();
	void natural_selection();
};
}

#endif /* TRAIN_TRAIN_H_ */
