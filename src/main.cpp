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

#include "Train/Train.h"

int main(){
	Train train(3);
	train.load_data();
    cin.get();
	return 0;
}
