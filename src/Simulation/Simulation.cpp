/*
 * Simulation.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: sakex
 */

#include "Simulation.h"

const string EVENT_TICK = "tick";

Simulation::Simulation() {
	// TODO Auto-generated constructor stub

}

Simulation::~Simulation() {
	// TODO Auto-generated destructor stub
}

void Simulation::on(std::string eventName, void (* function)(void *)){
	if(eventName == EVENT_TICK){
		tickEvent.addListener(function);
	}
	else{
		throw "Invalid event name";
	}
}

void Simulation::tick() const{
	tickEvent.emit();
}

void Simulation::tick(void * newData) const{
	tickEvent.emit(newData);
}



