/*
 * Serializable.cpp
 *
 *  Created on: Aug 16, 2019
 *      Author: sakex
 */

#include "Serializable.h"

namespace Serializer {

Serializable::Serializable() {

}

Serializable::~Serializable() {
}

std::string Serializable::to_string() const {
	return parse_to_string();
}
} /* namespace Serializer */
