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
	explicit Phenotype(int input[2], float weight);
	explicit Phenotype(int input[2]): Phenotype(input, .1) {}
	explicit Phenotype(int input[2], int output[2], float weight);

	void update_weight(float const & gradient);
	void set_output(int first, int second);
	int * get_input();
	int * get_output();
	float get_weight() const;

	void resize(int const & former_size, int const & new_size);

private:
	int input[2] = {};
	int output[2] = {};
	float weight;
};

}


#endif /* NEURALNETWORK_PHENOTYPE_H_ */
