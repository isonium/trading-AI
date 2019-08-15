/*
 * Parser.h
 *
 *  Created on: Aug 14, 2019
 *      Author: sakex
 */

#ifndef PARSER_PARSER_H_
#define PARSER_PARSER_H_

#include <functional>
#include <vector>
#include "../AlpacaServiceHTTP/AlpacaServiceHTTP.h"
#include "../Game/Game.h"

namespace fetch {

class Parser {
public:
	virtual ~Parser(){}

	virtual void load_data(std::function<void()> & cb) = 0;

private:
	virtual void parse_data(Response * res) = 0;
};

} /* namespace fetch */

#endif /* PARSER_PARSER_H_ */