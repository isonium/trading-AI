/*
 * Game.cpp
 *
 *  Created on: Aug 16, 2019
 *      Author: sakex
 */

#include "Game.h"

namespace Game {

Game::~Game(){}

void Game::run_generation() {
	do_run_generation();
}

void Game::get_results(std::vector<double> & output_vec) {
	do_get_results(output_vec);
}


void Game::reset_players(std::vector<Topology_ptr> & topologies) {
	do_reset_players(topologies);
}

}
