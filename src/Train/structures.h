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

struct TraderResult {
	const double wealth;
	std::shared_ptr<Trader> trader;
	NeuralNetwork::Topology topology;
};

}

#endif /* TRAIN_STRUCTURES_H_ */
