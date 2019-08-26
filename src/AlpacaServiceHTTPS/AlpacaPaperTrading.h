/*
 * AlpacaPaperTrading.h
 *
 *  Created on: Aug 26, 2019
 *      Author: sakex
 */

#ifndef ALPACASERVICEHTTPS_ALPACAPAPERTRADING_H_
#define ALPACASERVICEHTTPS_ALPACAPAPERTRADING_H_

#include "../HTTPS/HTTPS.h"

namespace Alpaca {

class AlpacaPaperTrading: public network::HTTPS<AlpacaPaperTrading> {
public:
	AlpacaPaperTrading();
	virtual ~AlpacaPaperTrading();

	void place_order();

protected:
	header_map const & headers();

private:
	header_map _headers =
			{ { "APCA-API-KEY-ID", "PKHKND8U0PRCWVVRRRK0" }, {
					"APCA-API-SECRET-KEY",
					"zyGVtBINUWR/nQiC3wpVZqsbFZ80kwtXAGtqVe0o" } };
};

} /* namespace Alpaca */

#endif /* ALPACASERVICEHTTPS_ALPACAPAPERTRADING_H_ */
