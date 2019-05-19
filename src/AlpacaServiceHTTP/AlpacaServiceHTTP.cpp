/*
 * AlpacaServiceHTTP.cpp
 *
 *  Created on: May 12, 2019
 *      Author: sakex
 */

#include "AlpacaServiceHTTP.h"


void AlpacaServiceHTTP::get(std::string path, void (*callback)(Response *))
{
	AlpacaServiceHTTP service;
	service._get(path, callback);
}


AlpacaServiceHTTP::AlpacaServiceHTTP():
	context(boost::asio::ssl::context::sslv23),
	resolver(io_context),
	response_stream(&response),
	socket(io_context, context)
{
	context.set_default_verify_paths();
	socket.set_verify_mode(boost::asio::ssl::verify_peer);
	socket.set_verify_callback(boost::asio::ssl::rfc2818_verification(host));
};

AlpacaServiceHTTP::~AlpacaServiceHTTP() {
	// TODO Auto-generated destructor stub
}

void AlpacaServiceHTTP::_get(std::string path, void (*callback)(Response *))
{
	fetch(path, "GET ", callback);
	io_context.run();
}


void AlpacaServiceHTTP::fetch(const std::string path, const std::string method, void (*callback)(Response *))
{
	//make request
	event.addListener(callback);

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

void AlpacaServiceHTTP::on_resolve(const boost::system::error_code& err, const tcp::resolver::results_type& endpoints) {
	if(err) handle_error("Resolve", err);


    boost::asio::async_connect(socket.lowest_layer(), endpoints,
    		boost::bind(&AlpacaServiceHTTP::on_connect, this, boost::asio::placeholders::error));
}

void AlpacaServiceHTTP::on_connect(const boost::system::error_code& err) {
    if (err) handle_error("Connect", err);

	socket.async_handshake(boost::asio::ssl::stream_base::client,
							boost::bind(&AlpacaServiceHTTP::on_handshake, this,
										boost::asio::placeholders::error));
}


void AlpacaServiceHTTP::on_handshake(const boost::system::error_code& err) {
	if(err) handle_error("Handshake", err);
	// The handshake was successful. Send the request.
	boost::asio::async_write(socket, request_buffer,
							 boost::bind(&AlpacaServiceHTTP::write_request, this,
										 boost::asio::placeholders::error));
}

void AlpacaServiceHTTP::write_request(const boost::system::error_code& err) {
    if (err) handle_error("Write request", err);

    boost::asio::async_read_until(socket, response, "\r\n",
                                  	  boost::bind(&AlpacaServiceHTTP::read_lines, this,
                                      boost::asio::placeholders::error, &response));
}


void AlpacaServiceHTTP::read_lines(const boost::system::error_code& err, boost::asio::streambuf* response) {
    if (err) handle_error("Read response", err);
	std::istream response_stream(response);
	std::string http_version;
	response_stream >> http_version;
	unsigned int status_code;
	response_stream >> res.status_code;
	std::string status_message;
	std::getline(response_stream, status_message);
	if (!response_stream || http_version.substr(0, 5) != "HTTP/")
	{
		std::cerr << "Invalid response\n";
		return;
	}

	// Read the response headers, which are terminated by a blank line.
	boost::asio::async_read_until(socket, *response, "\r\n\r\n",
								  boost::bind(&AlpacaServiceHTTP::read_headers, this,
											  boost::asio::placeholders::error, response));
}

void AlpacaServiceHTTP::read_headers(const boost::system::error_code& err, boost::asio::streambuf* response)
{
    if(err) handle_error("Read headers", err);
        // Process the response headers.

	std::string header;
	while (std::getline(response_stream, header) && header != "\r")
		res.headers += header;

	// Write whatever content we already have to output.
	if (response->size() > 0)
		response_stream >> res.body;

	// Start reading remaining data until EOF.
	boost::asio::async_read(socket, *response,
							boost::asio::transfer_at_least(1),
							boost::bind(&AlpacaServiceHTTP::read_body, this,
										boost::asio::placeholders::error, response));
}


void AlpacaServiceHTTP::read_body(const boost::system::error_code& err, boost::asio::streambuf* response){
    if (err){
		event.emit(&res);
		return;
    }
    std::string temp;
	response_stream >> temp;
	res.body += temp;
	boost::asio::async_read(socket, *response,
							boost::asio::transfer_at_least(1),
							boost::bind(&AlpacaServiceHTTP::read_body, this,
										boost::asio::placeholders::error, response));
}

void AlpacaServiceHTTP::handle_error(std::string what, boost::system::error_code ec){
	std::cerr << what << ": " << ec.message() << " [" << ec.value() << " ]" << std::endl;
    throw ec.message();
}


