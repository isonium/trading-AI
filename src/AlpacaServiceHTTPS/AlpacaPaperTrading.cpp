/*
 * AlpacaPaperTrading.cpp
 *
 *  Created on: Aug 26, 2019
 *      Author: sakex
 */

#include "AlpacaPaperTrading.h"

namespace Alpaca {

AlpacaPaperTrading::AlpacaPaperTrading(): HTTPS<AlpacaPaperTrading>("paper-api.alpaca.markets") {

}

AlpacaPaperTrading::~AlpacaPaperTrading() {
	// TODO Auto-generated destructor stub
}

network::HTTPS<AlpacaPaperTrading>::header_map const & AlpacaPaperTrading::headers(){
	return _headers;
}

void AlpacaPaperTrading::place_order(){
}

} /* namespace Alpaca */
