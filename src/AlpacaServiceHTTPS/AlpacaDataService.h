/*
 * AlpacaParserHTTPS.h
 *
 *  Created on: Aug 25, 2019
 *      Author: sakex
 */

#ifndef ALPACASERVICEHTTPS_ALPACADATASERVICE_H_
#define ALPACASERVICEHTTPS_ALPACADATASERVICE_H_

#include "../HTTPS/HTTPS.h"

namespace Alpaca {

class AlpacaDataService: public network::HTTPS<AlpacaDataService> {
public:
	AlpacaDataService();
	~AlpacaDataService();

protected:
	header_map const & headers();

private:
	header_map _headers =
			{ { "APCA-API-KEY-ID", "PKHKND8U0PRCWVVRRRK0" }, {
					"APCA-API-SECRET-KEY",
					"zyGVtBINUWR/nQiC3wpVZqsbFZ80kwtXAGtqVe0o" } };

};

} /* namespace Alpaca */

#endif /* ALPACASERVICEHTTPS_ALPACADATASERVICE_H_ */
