/*
 * Phenotype.h
 *
 *  Created on: Jul 28, 2019
 *      Author: sakex
 */

#ifndef NEURALNETWORK_PHENOTYPE_H_
#define NEURALNETWORK_PHENOTYPE_H_


namespace NeuralNetwork {

class Phenotype {
public:
	Phenotype(int input[2], float weight);
	Phenotype(int input[2]): Phenotype(input, .1) {}

	void update_weight(float gradient);
	void set_output(int first, int second);
	int * get_input();
	int * get_output();
	float get_weight() const;

private:
	int input[2];
	int output[2];
	float weight;
};

}


#endif /* NEURALNETWORK_PHENOTYPE_H_ */
