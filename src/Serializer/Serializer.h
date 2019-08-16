/*
 * Serializer.h
 *
 *  Created on: Aug 16, 2019
 *      Author: sakex
 */

#ifndef SERIALIZER_SERIALIZER_H_
#define SERIALIZER_SERIALIZER_H_

#include "Serializable.h"
#include <fstream>
#include <string>
#include <iostream>

namespace Serializer {

void to_file(Serializable * serializable, std::string file_name);

} /* namespace Serializer */

#endif /* SERIALIZER_SERIALIZER_H_ */
