/*
 * structures.h
 *
 *  Created on: Aug 1, 2019
 *      Author: sakex
 */

#ifndef TRAIN_STRUCTURES_H_
#define TRAIN_STRUCTURES_H_

#include <memory>
#include "../Trader/Trader.h"
#include "../NeuralNetwork/Topology.h"

namespace Train {
using namespace NeuralNetwork;

struct TraderResult {
	double wealth;
	std::shared_ptr<Topology> topology;

	const bool operator<(const TraderResult& comparison) const {
		return this->wealth < comparison.wealth;
	}

	const bool operator>(const TraderResult& comparison) const {
		return this->wealth > comparison.wealth;
	}
};

}

#endif /* TRAIN_STRUCTURES_H_ */
