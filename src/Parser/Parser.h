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
#include "../Game/Game.h"
#include "../HTTPS/HTTPS.h"

namespace fetch {

class Parser {
public:
	virtual ~Parser();

	void load_data(std::function<void()> & cb);

private:
	virtual void do_load_data(std::function<void()> & cb) = 0;
	virtual void parse_data(network::Response * res) = 0;
};

} /* namespace fetch */

#endif /* PARSER_PARSER_H_ */
