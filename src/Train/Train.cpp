/*
 * Train.cpp
 *
 *  Created on: May 26, 2019
 *      Author: sakex
 */

#include "Train.h"

constexpr int MAX_INDIVIDUALS = 500;

namespace Train {

Train::Train(Game::Game * game, int const initial_topology_count,
		int const inputs, int const outputs) :
		best_historical_topology { 0, Topology_ptr { NULL } } {
	this->game = game;
	this->inputs_count = inputs;
	this->outputs_count = outputs;
	random_new_topologies(initial_topology_count, inputs, outputs);
}

Train::~Train() {
}

void Train::random_new_topologies(int const initial_topology_count,
		int const inputs, int const outputs) {
	for (int count = 0; count < initial_topology_count; ++count) {
		Topology_ptr initial_topology = std::make_shared<Topology>();
		initial_topology->set_layers(2);
		for (int i = 0; i < inputs; ++i) {
			Phenotype::point input = { 0, i };
			float weight = (std::rand() % 100) / 100.0;
			Phenotype * phenotype = new Phenotype(input, weight);
			for (int j = 0; j < outputs; ++j) {
				phenotype->set_output(1, j);
				initial_topology->add_relationship(phenotype, true);
			}
		}
		topologies.emplace_back(std::move(initial_topology));
	}
}

void Train::reset_players() {
	game->reset_players(topologies);
}

void Train::start() {
	for (size_t it = 0; it < 500; ++it) {
		reset_players();
		auto start = std::chrono::high_resolution_clock::now();
		run_dataset();
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
				stop - start);
		cout << "TIME ELAPSED: " << duration.count() << endl;
		natural_selection();
	}
	Topology_ptr best_topology = best_historical_topology.topology;
	Topology * topology = best_topology.get();
	Serializer::to_file(topology, "t.json");
	std::cout << "DONE" << std::endl;
	std::cout << "RICHEST OVERALL: " << best_historical_topology.wealth
			<< std::endl;
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
	reset_topologies(results, topologies_size);
	update_best(results[topologies_size - 1]);
}

void Train::reset_topologies(TraderResult * results, int topologies_size) {
	std::sort(results, results + topologies_size);
	int quarter =
			topologies_size > MAX_INDIVIDUALS ?
					MAX_INDIVIDUALS / 4 : topologies_size / 4;
	for (int it = 0; it < topologies_size; ++it) {
		const double & wealth = results[it].wealth;
		Topology_ptr & topology = results[it].topology;
		if (topology->optimize(wealth)) {
			topologies.push_back(topology);
		} else if (it >= quarter) {
			int new_individuals = (MAX_INDIVIDUALS
					- static_cast<int>(topologies.size()))
					/ (topologies_size - it);
			if (new_individuals <= 0)
				new_individuals = 1;
			topology->new_generation(new_individuals, topologies, wealth);
		}
	}
	int end_size = topologies.size();
	if (end_size < MAX_INDIVIDUALS)
		random_new_topologies(MAX_INDIVIDUALS - end_size, inputs_count,
				outputs_count);
}

void Train::update_best(TraderResult & most_successful) {
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
