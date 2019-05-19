/*
 * main.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: sakex
 */

#include <iostream>
#include <unistd.h>
#include <string>
#include <nlohmann/json.hpp>

#include "Simulation/Simulation.h"
#include "Trader/Trader.h"
#include "AlpacaServiceHTTP/AlpacaServiceHTTP.h"

using json = nlohmann::json;
using namespace std;

void cb(Response * data){
	std::cout << data->body;
}

int main(){

    AlpacaServiceHTTP::get("/v1/account", &cb);
    cin.get();
	return 0;
}
