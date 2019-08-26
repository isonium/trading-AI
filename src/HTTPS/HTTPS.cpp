/*
 * HTTPS.cpp
 *
 *  Created on: May 12, 2019
 *      Author: sakex
 */

#include "HTTPS.h"

namespace network {

void Response::print_headers() const {
	for (auto & it : headers) {
		std::cout << it.first << ": " << it.second << std::endl;
	}
}
}

