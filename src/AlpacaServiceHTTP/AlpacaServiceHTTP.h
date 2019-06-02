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
#include <unordered_map>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>

#include "../Event/Event.hpp"

using boost::asio::ip::tcp;


typedef struct {
	std::string body;
	std::unordered_map<std::string, std::string> headers;
	unsigned int status_code;
	void print_headers() const;
} Response;


class AlpacaServiceHTTP {
public:
	template<class CBtype>
	static void get(std::string path, CBtype cb)
	{
		AlpacaServiceHTTP service;
		service._get(path, cb);
	}

	template<class CBtype>
	static void post(const std::string path, CBtype cb)
	{
		AlpacaServiceHTTP service;
		service._post(path, cb);
	}

	virtual ~AlpacaServiceHTTP();

	template<class CBtype>
    void _get(std::string path, CBtype cb)
	{
		fetch(path, "GET ", cb);
		io_context.run();
	}

	template<class CBtype>
    void _post(std::string path, CBtype cb)
	{
		fetch(path, "POST ", cb);
		io_context.run();
	}



private:
    const std::string host = "data.alpaca.markets";
    const std::string keyId = "PKHKND8U0PRCWVVRRRK0";
    const std::string secret = "zyGVtBINUWR/nQiC3wpVZqsbFZ80kwtXAGtqVe0o";

    boost::asio::ssl::context context;
	boost::asio::io_context io_context;
	tcp::resolver resolver;
    boost::asio::ssl::stream<tcp::socket> socket;
    boost::asio::streambuf request_buffer;
    boost::asio::streambuf response;
    std::istream response_stream;

    Response res;
    Event<Response*> event;

    AlpacaServiceHTTP();

    template<class CBtype>
    void fetch(const std::string path, const std::string method, CBtype cb)
    {
    	//make request
    	event.addListener(cb);

    	std::ostream request_stream(&request_buffer);
    	request_stream << method << path << " HTTP/1.0\r\n";
    	request_stream << "Host: " << host << "\r\n";
    	request_stream << "Accept: */*\r\n";
    	request_stream << "APCA-API-KEY-ID: " << keyId << "\r\n";
    	request_stream << "APCA-API-SECRET-KEY: " << secret << "\r\n";
    	request_stream << "Connection: close\r\n\r\n";

    	// Find endpoint

    	resolver.async_resolve(host, "https",
    					boost::bind(&AlpacaServiceHTTP::on_resolve, this,
    					boost::asio::placeholders::error,
    					boost::asio::placeholders::results));
    }

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
