/*
 * main.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: sakex
 */

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <time.h>
#include <functional>
#include <exception>
#include <nlohmann/json.hpp>

#include "Train/Train.h"
#include "Trader/Simulation.h"
#include "Trader/LiveTrading.h"
#include "AlpacaParser/AlpacaParser.h"
#include "AlpacaServiceHTTPS/AlpacaDataService.h"

struct InvalidArguments: public std::exception {
	std::string invalid;
	int reason;

	InvalidArguments(int expected, int count) {
		invalid = std::to_string(expected) + " expepted. "
				+ std::to_string(count) + " received";
		reason = 0;
	}

	InvalidArguments(std::string arg) {
		invalid = arg;
		reason = 1;
	}

	const char * what() const throw () {
		std::string str;
		if (reason == 0) {
			str = "Invalid number of arguments, " + invalid;
		}
		if (reason == 1)
			str = "Invalid argument: " + invalid
					+ " received. Expected either train or start";
		char * cstr = new char[str.length() + 1];
		std::strcpy(cstr, str.c_str());
		return cstr;
	}
};

void train() {
	Alpaca::AlpacaParser parser;
	std::function<void()> && lambda = [&parser]() {
		std::vector<stock::Candle *> & data = parser.get_data();
		Trading::Simulation * sim = new Trading::Simulation(data);
		Train::Train train(sim, 100, 7, 1);
		train.start();
	};
	parser.load_data(lambda);
}

void start_bot(const char * input_file) {
	using json = nlohmann::json;

	std::ifstream file(input_file);
	json j = json::parse(file);
	Topology_ptr topology = std::make_unique<Topology>(j);
	Trading::LiveTrading game (topology);
}

int main(int const argc, const char * argv[]) {
	std::string action = argv[1];
	if (action == "train") {
		if (argc != 2) {
			throw InvalidArguments(2, argc);
		}
		srand(time(NULL));
		train();
	} else if (action == "start") {
		if (argc != 3) {
			throw InvalidArguments(3, argc);
		}
		start_bot(argv[2]);
	} else {
		throw InvalidArguments(action);
	}
	return 0;
}
