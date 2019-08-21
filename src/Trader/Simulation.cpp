/*
 * Simulation.cpp
 *
 *  Created on: Aug 14, 2019
 *      Author: sakex
 */

#include "Simulation.h"

namespace Trading {
constexpr long double k100 = 100000;

Simulation::Simulation(std::vector<stock::Candle *> & _data) {
	for (stock::Candle * data_point : _data)
		data.push_back(data_point);
	state = new State { (data[0]), new stock::Stock { "Apple", "AAPL", 0 } };
	std::cout << "STOCK PERFORMANCE: "
			<< (data.back()->close - data[0]->open) / data[0]->open << std::endl;
}

Simulation::~Simulation() {
	delete state->default_stock;
	delete state;
}

void Simulation::do_reset_players(std::vector<Topology_ptr> & topologies) {
	size_t topologies_size = topologies.size();
	size_t former_players_size = players.size();
	players.resize(topologies_size);
	if (topologies_size > former_players_size) {
		for (size_t it = former_players_size; it < topologies_size; ++it) {
			std::shared_ptr<Topology> topology = topologies[it];
			std::shared_ptr<Trader> trader = std::make_shared<Trader>(k100,
					topology, state);
			players[it] = trader;
		}
	} else {
		former_players_size = topologies_size;
	}
	for (size_t it = 0; it < former_players_size; ++it) {
		players[it]->reset(topologies[it]);
	}
}

void Simulation::update_state(stock::Candle * candle) {
	state->default_stock->value = (candle->open + candle->close) / 2;
	state->candle = candle;
}

void Simulation::do_run_generation() {
	for (stock::Candle * candle : data) {
		update_state(candle);
		std::function<void(std::shared_ptr<Trader> &)> lambda =
				[](std::shared_ptr<Trader>  &trader) -> void {trader->decide();};
		Threading::forEach(players.begin(), players.end(), lambda);
		//std::for_each(players.begin(), players.end(), lambda);
	}
}

void Simulation::do_get_results(std::vector<double> & results) {
	for (Trader_ptr & trader : players) {
		results.push_back(trader->get_result());
	}
}

} /* namespace Trader */
