/*
 * Game.h
 *
 *  Created on: Aug 14, 2019
 *      Author: sakex
 */

#ifndef GAME_GAME_H_
#define GAME_GAME_H_

#include <vector>
#include <memory>
#include "../NeuralNetwork/Topology.h"
#include "Player.h"
#include "Empty.h"

using namespace NeuralNetwork;
namespace Game {

class Game {
public:
	virtual ~Game() {
	}

	virtual void reset_players(std::vector<Topology_ptr> &) = 0;

	virtual void run_generation() = 0;

	virtual void get_results(std::vector<double> &) = 0;
};
}

#endif /* GAME_GAME_H_ */
