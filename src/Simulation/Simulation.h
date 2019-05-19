/*
 * Simulation.h
 *
 *  Created on: Apr 6, 2019
 *      Author: sakex
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include "../Event/Event.hpp"

class Simulation {
public:
	Simulation();
	virtual ~Simulation();

	void tick() const;
	void tick(void * newData) const;
	void on(std::string eventName, void (* function)(void *));

private:
	Event<void *> tickEvent;
};

#endif /* SIMULATION_H_ */
