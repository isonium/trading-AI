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

#include "../Simulation/Simulation.h"
#include "../Trader/Trader.h"
#include "../AlpacaServiceHTTP/AlpacaServiceHTTP.h"
#include "../Event/Event.hpp"
#include "../Stock/Stock.h"
#include "../NeuralNetwork/Topology.h"
#include "../NeuralNetwork/NN.h"

using json = nlohmann::json;

class Train {
public:
	Train(int initial_topology_count, int inputs, int outputs);
	virtual ~Train();

	void load_data();

private:
	Simulation simulation;
	std::vector<stock::Candle> data;
	std::vector<NeuralNetwork::Topology> topologies;

	void parse_data(Response * data);
	void start();
	void init_traders();
};

#endif /* TRAIN_TRAIN_H_ */
