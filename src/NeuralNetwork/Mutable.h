/*
 * Mutable.h
 *
 *  Created on: Jul 27, 2019
 *      Author: sakex
 */

#ifndef NEURALNETWORK_MUTABLE_H_
#define NEURALNETWORK_MUTABLE_H_

namespace NeuralNetwork{

class Mutable{
public:
	virtual void mutate() = 0;
	virtual ~Mutable(){};
};

} /* namespace NeuralNetwork */

#endif /* NEURALNETWORK_MUTABLE_H_ */
