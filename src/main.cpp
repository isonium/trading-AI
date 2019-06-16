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

#include "Train/Train.h"


int main(){
	Train train(100, 7, 1);
	train.load_data();
	return 0;
}
