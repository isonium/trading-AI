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
#include <nlohmann/json.hpp>
#include <time.h>
#include <functional>

#include "Train/Train.h"
#include "Trader/Simulation.h"
#include "AlpacaParser/AlpacaParser.h"

void start() {
	DataParser::AlpacaParser parser;
	std::function<void()> && lambda = [&parser](){
		std::vector<stock::Candle *> & data = parser.get_data();
		Trading::Simulation * sim = new Trading::Simulation(data);
		Train::Train train(sim, 100, 7, 1);
		train.start();
	};
	parser.load_data(lambda);
}

int main() {
	srand (time(NULL));
	start();
	return 0;
}
