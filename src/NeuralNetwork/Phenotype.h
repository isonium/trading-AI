/*
 * Phenotype.h
 *
 *  Created on: Jul 28, 2019
 *      Author: sakex
 */

#ifndef NEURALNETWORK_PHENOTYPE_H_
#define NEURALNETWORK_PHENOTYPE_H_

#include <array>
#include <boost/functional/hash.hpp>
#include "../Serializer/Serializer.h"

namespace NeuralNetwork {

class Phenotype: public Serializer::Serializable {
public:
	using point = std::array<int, 2>;

	explicit Phenotype(point const & input, double const weight);
	explicit Phenotype(point const & input): Phenotype(input, .1) {}
	explicit Phenotype(point const & input, point const & output, double const weight);

	void set_weight(double const gradient);
	void set_output(int const first, int const second);
	point const & get_input();
	point const & get_output();
	double get_weight() const;
	void decrement_output();

	void resize(int const former_size, int const new_size);

	void disable();
	bool is_disabled() const;

	bool same_output(Phenotype const &) const;

private:
	point input;
	point output;
	double weight;
	bool disabled = false;

	std::string parse_to_string() const;
};

}

namespace std {
template<> struct hash<NeuralNetwork::Phenotype::point> {
	size_t operator()(const NeuralNetwork::Phenotype::point & p) const {
		std::size_t seed = 0;
		boost::hash_combine(seed, p[0]);
		boost::hash_combine(seed, p[1]);
		return seed;
	}
};
}


#endif /* NEURALNETWORK_PHENOTYPE_H_ */
