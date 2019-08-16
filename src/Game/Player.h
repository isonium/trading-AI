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
	virtual ~Player();

	void decide();

	void reset(NeuralNetwork::Topology_ptr &);

	double get_result() const;

private:
	virtual void do_decide() = 0;
	virtual void do_reset(NeuralNetwork::Topology_ptr & brain_topology) = 0;
	virtual double do_get_result() const = 0;
};
}

#endif /* GAME_PLAYER_H_ */
