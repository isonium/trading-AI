/*
 * HTTPS.h
 *
 *  Created on: May 12, 2019
 *      Author: sakex
 */

#ifndef HTTPS_H_
#define HTTPS_H_

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

namespace network {
using boost::asio::ip::tcp;

typedef struct {
	std::string body;
	std::unordered_map<std::string, std::string> headers;
	unsigned int status_code;
	void print_headers() const;
} Response;

template<class Service>
class HTTPS {
public:
	HTTPS(std::string const & __host) :
			context(boost::asio::ssl::context::sslv23), resolver(io_context), response_stream(
					&response), socket(io_context, context), res() {
		_host = __host;
		context.set_default_verify_paths();
		socket.set_verify_mode(boost::asio::ssl::verify_peer);
		socket.set_verify_callback(
				boost::asio::ssl::rfc2818_verification(_host));
	}

	virtual ~HTTPS() {
	}

	template<class CBtype>
	static void get(std::string path, CBtype cb) {
		Service service;
		service._get(path, cb);
	}

	template<class CBtype>
	static void post(const std::string & path, CBtype cb) {
		Service service;
		service._post(path, cb);
	}

protected:
	using header_map = std::unordered_map<std::string, std::string>;
	std::string _host;
	virtual header_map const & headers() = 0;
	std::string & host() {
		return _host;
	}

	template<typename CBtype>
	void _get(std::string const & path, CBtype cb) {
		event.addListener(cb);
		std::ostream request_stream(&request_buffer);
		write_headers(path, "GET ", request_stream);
		resolve(request_stream);
		io_context.run();
	}

	template<typename CBtype>
	void _post(std::string const & path, CBtype cb) {
		event.addListener(cb);
		std::ostream request_stream(&request_buffer);
		write_headers(path, "GET ", request_stream);
		resolve(request_stream);
		io_context.run();
	}

private:
	boost::asio::ssl::context context;
	boost::asio::io_context io_context;
	tcp::resolver resolver;
	std::istream response_stream;
	boost::asio::ssl::stream<tcp::socket> socket;
	boost::asio::streambuf request_buffer;
	boost::asio::streambuf response;

	Response res;
	Event<Response*> event;

	void write_headers(std::string const & path, std::string const & method,
			std::ostream & request_stream) {
		request_stream << method << path << " HTTP/1.0\r\n";
		request_stream << "Host: " << _host << "\r\n";
		request_stream << "Accept: */*\r\n";
		for (std::pair<std::string, std::string> const & header : headers()) {
			request_stream << header.first << ": " << header.second << "\r\n";
		}
	}

	void resolve(std::ostream & request_stream) {
		request_stream << "Connection: close\r\n\r\n";

		resolver.async_resolve(_host, "https",
				boost::bind(&HTTPS<Service>::on_resolve, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::results));
	}

	void on_resolve(const boost::system::error_code& err,
			const tcp::resolver::results_type& endpoints) {
		if (err)
			handle_error("Resolve", err);

		boost::asio::async_connect(
				// @suppress("Invalid arguments")
				socket.lowest_layer(), endpoints,
				boost::bind(&HTTPS<Service>::on_connect, this,
						boost::asio::placeholders::error));
	}

	void on_connect(const boost::system::error_code& err) {
		if (err)
			handle_error("Connect", err);

		socket.async_handshake(boost::asio::ssl::stream_base::client,
				boost::bind(&HTTPS<Service>::on_handshake, this,
						boost::asio::placeholders::error));
	}

	void on_handshake(const boost::system::error_code& err) {
		if (err)
			handle_error("Handshake", err);
		// The handshake was successful. Send the request.
		boost::asio::async_write(socket, request_buffer,
				boost::bind(&HTTPS<Service>::write_request, this,
						boost::asio::placeholders::error));
	}

	void write_request(const boost::system::error_code& err) {
		if (err)
			handle_error("Write request", err);

		boost::asio::async_read_until(socket, response, "\r\n",
				boost::bind(&HTTPS<Service>::read_lines, this,
						boost::asio::placeholders::error, &response));
	}

	void read_lines(const boost::system::error_code& err,
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
				boost::bind(&HTTPS<Service>::read_headers, this,
						boost::asio::placeholders::error, response));
	}

	void read_headers(const boost::system::error_code& err,
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
				boost::bind(&HTTPS<Service>::read_body, this,
						boost::asio::placeholders::error, response));
	}

	void read_body(const boost::system::error_code& err,
			boost::asio::streambuf* response) {
		if (!err) {
			boost::asio::async_read(socket, *response,
					boost::asio::transfer_at_least(1),
					boost::bind(&HTTPS<Service>::read_body, this,
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

	void handle_error(std::string const & what, boost::system::error_code ec) {
		std::cerr << what << ": " << ec.message() << " [" << ec.value() << "]"
				<< std::endl;
		throw ec.message();
	}

	static std::vector<std::string> * get_header_pair(
			std::string const & header) {
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
};
}
#endif /* HTTPS_H_ */
