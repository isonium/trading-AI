/*
 * AlpacaServiceHTTP.h
 *
 *  Created on: May 12, 2019
 *      Author: sakex
 */

#ifndef ALPACASERVICEHTTP_H_
#define ALPACASERVICEHTTP_H_


#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>

#include "../Event/Event.hpp"

using boost::asio::ip::tcp;

typedef struct {
	std::string body;
	std::string headers;
	unsigned int status_code;
} Response;


class AlpacaServiceHTTP {
public:
	static void get(std::string path, void (*callback)(Response *));

	AlpacaServiceHTTP();

	virtual ~AlpacaServiceHTTP();

    void _get(std::string path, void (*callback)(Response *));

    /*
    void post(std::string path){
    	fetch(path, "POST ");
    };*/


private:
    std::string host = "paper-api.alpaca.markets";
    std::string keyId = "PKHKND8U0PRCWVVRRRK0";
    std::string secret = "zyGVtBINUWR/nQiC3wpVZqsbFZ80kwtXAGtqVe0o";

    boost::asio::ssl::context context;
	boost::asio::io_context io_context;
	tcp::resolver resolver;
    boost::asio::ssl::stream<tcp::socket> socket;
    boost::asio::streambuf request_buffer;
    boost::asio::streambuf response;
    std::istream response_stream;

    Response res;
    Event<Response*> event;

    void fetch(const std::string path, const std::string method, void (*callback)(Response *));
    void on_resolve(const boost::system::error_code& err, const tcp::resolver::results_type& endpoints);
    void on_connect(const boost::system::error_code& err);
    void on_handshake(const boost::system::error_code& error);
    void write_request(const boost::system::error_code& err);
    void read_lines(const boost::system::error_code& err, boost::asio::streambuf* response);
    void read_headers(const boost::system::error_code& err, boost::asio::streambuf* response);
    void read_body(const boost::system::error_code& err, boost::asio::streambuf* response);
    void handle_error(std::string what, boost::system::error_code ec);
};

#endif /* ALPACASERVICEHTTP_H_ */
