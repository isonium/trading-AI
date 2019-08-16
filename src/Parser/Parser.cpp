/*
 * Parser.cpp
 *
 *  Created on: Aug 16, 2019
 *      Author: sakex
 */




#include "Parser.h"

namespace fetch {

Parser::~Parser() {
}

void Parser::load_data(std::function<void()> & cb) {
	do_load_data(cb);
}


}
