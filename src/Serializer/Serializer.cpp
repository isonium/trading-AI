/*
 * Serializer.cpp
 *
 *  Created on: Aug 16, 2019
 *      Author: sakex
 */

#include "Serializer.h"

void Serializer::to_file(Serializable * serializable, std::string file_name) {
	std::string output = serializable->to_string();
	std::ofstream file (file_name);
	file << output;
	file.close();
}
