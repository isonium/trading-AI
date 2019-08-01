/*
 * AlpacaService.h
 *
 *  Created on: May 12, 2019
 *      Author: sakex
 */

#ifndef ALPACASERVICE_H_
#define ALPACASERVICE_H_

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

using json = nlohmann::json;
using tcp = boost::asio::ip::tcp;
// from <boost/asio/ip/tcp.hpp>
namespace websocket = boost::beast::websocket;
// from <boost/beast/websocket.hpp>

class AlpacaServiceWS: public std::enable_shared_from_this<AlpacaServiceWS> {
public:
	explicit AlpacaServiceWS() :
			resolver_(ioc), ws_(ioc) {
	}
	explicit AlpacaServiceWS(boost::asio::io_context& ioc) :
			resolver_(ioc), ws_(ioc) {
	}

	explicit AlpacaServiceWS(std::string host);
	virtual ~AlpacaServiceWS();

	void run(std::string host, std::string port, json data);
	void on_resolve(boost::system::error_code ec,
			tcp::resolver::results_type results);
	void on_connect(boost::system::error_code ec);
	void on_handshake(boost::system::error_code ec);
	void on_write(boost::system::error_code ec, std::size_t bytes_transferred);
	void on_read(boost::system::error_code ec, std::size_t bytes_transferred);
	void on_close(boost::system::error_code ec);

private:
	tcp::resolver resolver_;
	websocket::stream<tcp::socket> ws_;
	boost::beast::multi_buffer buffer_;
	std::string host_;
	json data_;
	boost::asio::io_context ioc;
};

#endif /* ALPACASERVICE_H_ */
