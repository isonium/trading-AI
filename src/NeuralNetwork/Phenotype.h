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

	void set_weight(float const & gradient);
	void set_output(int first, int second);
	int * get_input();
	int * get_output();
	double get_weight() const;

	void resize(int const & former_size, int const & new_size);

	void disable();
	bool is_disabled() const;

	bool operator==(Phenotype const &) const;

private:
	int input[2] = {};
	int output[2] = {};
	double weight;
	bool disabled = false;

};

}


#endif /* NEURALNETWORK_PHENOTYPE_H_ */
