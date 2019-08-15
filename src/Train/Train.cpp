/*
 * Train.cpp
 *
 *  Created on: May 26, 2019
 *      Author: sakex
 */

#include "Train.h"
#define MULTITHREADED

constexpr int MAX_INVIDUALS = 500;

namespace Train {

Train::Train(Game::Game * game, int const & initial_topology_count,
		int const & inputs, int const & outputs) {
	this->game = game;
	for (int count = 0; count < initial_topology_count; ++count) {
		Topology_ptr initial_topology = std::make_shared<Topology>();
		initial_topology->set_layers(2);
		for (int i = 0; i < inputs; ++i) {
			int input[2] = { 0, i };
			float weight = (std::rand() % 100) / 100.0;
			std::shared_ptr<Phenotype> phenotype = std::make_shared<Phenotype>(
					input, weight);
			for (int j = 0; j < outputs; ++j) {
				phenotype->set_output(1, j);
				initial_topology->add_relationship(phenotype, true);
			}
		}
		topologies.emplace_back(std::move(initial_topology));
	}
}

Train::~Train() {
}

void Train::reset_players() {
	game->reset_players(topologies);
}

void Train::start() {
	for (size_t it = 0; it < 1000; ++it) {
		reset_players();
		auto start = std::chrono::high_resolution_clock::now();
		run_dataset();
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
				stop - start);
		cout << "TIME ELAPSED: " << duration.count() << endl;
		natural_selection();
	}
	std::cout << "DONE" << std::endl;
}

void Train::run_dataset() {
	game->run_generation();
}

void Train::natural_selection() {
	std::vector<double> outcomes;
	game->get_results(outcomes);
	int topologies_size = topologies.size();
	TraderResult results[topologies_size];
	for (int it = 0; it < topologies_size; ++it) {
		Topology_ptr topology(topologies[it]);
		results[it] = TraderResult { outcomes[it], topology };
	}
	topologies.clear();

	std::sort(results, results + topologies_size);

	int quarter =
			topologies_size > MAX_INVIDUALS ?
					MAX_INVIDUALS / 4 : topologies_size / 4;
	int new_individuals = -1;
	for (int it = 0; it < topologies_size; ++it) {
		const double & wealth = results[it].wealth;
		Topology_ptr & topology = results[it].topology;
		if (topology->optimize(wealth)) {
			topologies.push_back(topology);
		} else if (it >= quarter) {
			if (new_individuals == -1) {
				new_individuals = (MAX_INVIDUALS - topologies.size())
						/ (topologies_size - it);
				if (new_individuals <= 0)
					new_individuals = 1;
			}
			topology->new_generation(new_individuals, topologies, wealth);
		}
	}
	TraderResult most_successful = results[topologies_size - 1];
	if (most_successful > best_historical_topology) {
		best_historical_topology.wealth = most_successful.wealth;
		best_historical_topology.topology = std::make_shared<Topology>(
				*(most_successful.topology));
	}
	best_historical_topology.topology->new_generation(3, topologies,
			best_historical_topology.wealth);
	std::cout << "Richest trader: " << most_successful.wealth << std::endl;
	std::cout << "SIZE: " << topologies.size() << std::endl;
}
}
