/*
 * AlpacaPaser.h
 *
 *  Created on: Aug 14, 2019
 *      Author: sakex
 */

#ifndef ALPACAPARSER_ALPACAPARSER_H_
#define ALPACAPARSER_ALPACAPARSER_H_

#include <nlohmann/json.hpp>
#include "../AlpacaServiceHTTP/AlpacaServiceHTTP.h"
#include "../Parser/Parser.h"
#include "../Stock/Stock.h"
#include <vector>
#include <functional>

namespace DataParser {
using json = nlohmann::json;

class AlpacaParser: public fetch::Parser {
public:
	~AlpacaParser();

	void load_data(std::function<void()> & cb);
	std::vector<stock::Candle*> & get_data();

private:
	std::vector<stock::Candle*> data;
	std::function<void()> callback;

	void parse_data(Response * res);
};

} /* namespace AlpacaParser */

#endif /* ALPACAPARSER_ALPACAPARSER_H_ */
