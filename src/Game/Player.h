/*
 * Player.h
 *
 *  Created on: Aug 14, 2019
 *      Author: sakex
 */

#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include "../NeuralNetwork/Topology.h"

namespace Game {

class Player {
public:
	virtual ~Player() {
	}

	virtual void decide() = 0;

	virtual void reset(NeuralNetwork::Topology_ptr & brain_topology) = 0;

	virtual double get_result() const = 0;
};
}

#endif /* GAME_PLAYER_H_ */
