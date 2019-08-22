/*
 * Train.h
 *
 *  Created on: May 26, 2019
 *      Author: sakex
 */

#ifndef TRAIN_TRAIN_H_
#define TRAIN_TRAIN_H_

#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>
#include <chrono>
#include <functional>
#include <stdlib.h>

#include "structures.h"
#include "../Trader/Trader.h"
#include "../Event/Event.hpp"
#include "../Stock/Stock.h"
#include "../NeuralNetwork/Topology.h"
#include "../NeuralNetwork/NN.h"
#include "../Game/Game.h"
#include "../Game/Player.h"
#include "../Parser/Parser.h"
#include "../Serializer/Serializer.h"

namespace Train {
using namespace NeuralNetwork;
using namespace Trading;

class Train {
public:
	Train(Game::Game * game, int const initial_topology_count, int const inputs,
			int const outputs);
	~Train();

	void start();

private:
	Game::Game * game;
	std::vector<Topology_ptr> topologies;
	TraderResult best_historical_topology;

	void reset_players();
	void run_dataset();
	void natural_selection();
	void reset_topologies(TraderResult * results, int topologies_size);
	void update_best(TraderResult & most_successful);
};
}

#endif /* TRAIN_TRAIN_H_ */
