/*
 * Simulation.h
 *
 *  Created on: Aug 14, 2019
 *      Author: sakex
 */

#ifndef TRADER_SIMULATION_H_
#define TRADER_SIMULATION_H_

#include "../Game/Game.h"
#include "../Game/Player.h"
#include "SimulationTrader.h"
#include "State.h"
#include "../NeuralNetwork/Topology.h"
#include "../Threading/multithreaded_methods.h"
#include <memory>

using namespace NeuralNetwork;
namespace Trading {

class Simulation: public Game::Game {
public:
	explicit Simulation(std::vector<stock::Candle *> & _data);
	virtual ~Simulation();

private:
	State * state;
	std::vector<SimulationTrader_ptr> players;
	std::vector<stock::Candle *> data;

	void update_state(stock::Candle * candle);

	void do_reset_players(std::vector<Topology_ptr> &);
	void do_run_generation();
	void do_get_results(std::vector<double> &);
};

} /* namespace Trader */

#endif /* TRADER_SIMULATION_H_ */
