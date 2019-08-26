/*
 * AlpacaParserHTTPS.cpp
 *
 *  Created on: Aug 25, 2019
 *      Author: sakex
 */

#include "AlpacaDataService.h"

namespace Alpaca {

AlpacaDataService::AlpacaDataService(): HTTPS<AlpacaDataService>("data.alpaca.markets") {
}

AlpacaDataService::~AlpacaDataService() {
}

network::HTTPS<AlpacaDataService>::header_map const & AlpacaDataService::headers(){
	return _headers;
}

} /* namespace Alpaca */
