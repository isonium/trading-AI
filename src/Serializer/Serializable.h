/*
 * Serializable.h
 *
 *  Created on: Aug 16, 2019
 *      Author: sakex
 */

#ifndef SERIALIZER_SERIALIZABLE_H_
#define SERIALIZER_SERIALIZABLE_H_

#include <string>

namespace Serializer {

class Serializable {
public:
	Serializable();
	virtual ~Serializable();

	std::string to_string() const;

private:
	virtual std::string parse_to_string() const = 0;
};

} /* namespace Serializer */

#endif /* SERIALIZER_SERIALIZABLE_H_ */
