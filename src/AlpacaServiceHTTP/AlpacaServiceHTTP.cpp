/*
 * AlpacaServiceHTTP.cpp
 *
 *  Created on: May 12, 2019
 *      Author: sakex
 */

#include "AlpacaServiceHTTP.h"

void Response::print_headers() const {
	for (auto it = headers.begin(); it != headers.end(); ++it) {
		std::cout << it->first << ": " << it->second << std::endl;
	}
}

AlpacaServiceHTTP::AlpacaServiceHTTP() :
		context(boost::asio::ssl::context::sslv23), resolver(io_context), response_stream(
				&response), socket(io_context, context), res() {
	context.set_default_verify_paths();
	socket.set_verify_mode(boost::asio::ssl::verify_peer);
	socket.set_verify_callback(boost::asio::ssl::rfc2818_verification(host));
}
;

AlpacaServiceHTTP::~AlpacaServiceHTTP() {
	// TODO Auto-generated destructor stub
}

void AlpacaServiceHTTP::on_resolve(const boost::system::error_code& err,
		const tcp::resolver::results_type& endpoints) {
	if (err)
		handle_error("Resolve", err);

	boost::asio::async_connect(socket.lowest_layer(), endpoints, // @suppress("Invalid arguments")
			boost::bind(&AlpacaServiceHTTP::on_connect, this,
					boost::asio::placeholders::error));
}

void AlpacaServiceHTTP::on_connect(const boost::system::error_code& err) {
	if (err)
		handle_error("Connect", err);

	socket.async_handshake(boost::asio::ssl::stream_base::client,
			boost::bind(&AlpacaServiceHTTP::on_handshake, this,
					boost::asio::placeholders::error));
}

void AlpacaServiceHTTP::on_handshake(const boost::system::error_code& err) {
	if (err)
		handle_error("Handshake", err);
	// The handshake was successful. Send the request.
	boost::asio::async_write(socket, request_buffer,
			boost::bind(&AlpacaServiceHTTP::write_request, this,
					boost::asio::placeholders::error));
}

void AlpacaServiceHTTP::write_request(const boost::system::error_code& err) {
	if (err)
		handle_error("Write request", err);

	boost::asio::async_read_until(socket, response, "\r\n",
			boost::bind(&AlpacaServiceHTTP::read_lines, this,
					boost::asio::placeholders::error, &response));
}

void AlpacaServiceHTTP::read_lines(const boost::system::error_code& err,
		boost::asio::streambuf* response) {
	if (err)
		handle_error("Read response", err);
	std::istream response_stream(response);
	std::string http_version;
	response_stream >> http_version;
	response_stream >> res.status_code;
	std::string status_message;
	std::getline(response_stream, status_message);
	if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
		std::cerr << "Invalid response\n";
		return;
	}

	// Read the response headers, which are terminated by a blank line.
	boost::asio::async_read_until(socket, *response, "\r\n",
			boost::bind(&AlpacaServiceHTTP::read_headers, this,
					boost::asio::placeholders::error, response));
}

std::vector<std::string> * get_header_pair(std::string const & header) {
	std::vector<std::string> * pair = new std::vector<std::string>();
	int size = header.size();
	for (int it = 0; it < size - 1; ++it) {
		if (header[it] == ':' && header[it + 1] == ' ') {
			std::string first = header.substr(0, it);
			std::string second = header.substr(it + 2, size - it - 3);
			pair->push_back(first);
			pair->push_back(second);
			return pair;
		}
	}
	delete pair;
	return NULL;
}

void AlpacaServiceHTTP::read_headers(const boost::system::error_code& err,
		boost::asio::streambuf* response) {
	if (err)
		handle_error("Read headers", err);
	// Process the response headers.

	std::string header;
	std::vector<std::string> * pair_ptr;
	while (std::getline(response_stream, header) && header != "\r") {
		pair_ptr = get_header_pair(header);
		res.headers[pair_ptr->at(0)] = pair_ptr->at(1);
	}
	delete pair_ptr;

	// Write whatever content we already have to output.

	// Start reading remaining data until EOF.
	boost::asio::async_read(socket, *response,
			boost::asio::transfer_at_least(1),
			boost::bind(&AlpacaServiceHTTP::read_body, this,
					boost::asio::placeholders::error, response));
}

void AlpacaServiceHTTP::read_body(const boost::system::error_code& err,
		boost::asio::streambuf* response) {
	if (!err) {
		boost::asio::async_read(socket, *response,
				boost::asio::transfer_at_least(1),
				boost::bind(&AlpacaServiceHTTP::read_body, this,
						boost::asio::placeholders::error, response));
	} else if (err == boost::asio::error::eof) {
		std::string body((std::istreambuf_iterator<char>(response)),
				std::istreambuf_iterator<char>());
		res.body = body;
		event.emit(&res);
		return;
	} else {
		handle_error("Error while reading response", err);
	}
}

void AlpacaServiceHTTP::handle_error(std::string const & what,
		boost::system::error_code ec) {
	std::cerr << what << ": " << ec.message() << " [" << ec.value() << "]"
			<< std::endl;
	throw ec.message();
}

