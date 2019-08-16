/*
 * Player.cpp
 *
 *  Created on: Aug 16, 2019
 *      Author: sakex
 */

#include "Player.h"

namespace Game {

Player::~Player() {
}

void Player::decide() {
	do_decide();
}

void Player::reset(NeuralNetwork::Topology_ptr & brain_topology) {
	do_reset(brain_topology);
}

double Player::get_result() const {
	return do_get_result();
}

}
