/*
 * AlpacaService.cpp
 *
 *  Created on: May 12, 2019
 *      Author: sakex
 */

#include "AlpacaServiceWS.h"

void fail(boost::system::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << " [" << ec.value() << "]" << "\n";
}

AlpacaServiceWS::~AlpacaServiceWS() {
	// TODO Auto-generated destructor stub
}


void AlpacaServiceWS::run(std::string host, std::string port, json data){
    // Normal boost::asio setup
    host_ = host;
    data_ = data;

    // Look up the domain name
    resolver_.async_resolve(
        host,
        port,
        std::bind(
            &AlpacaServiceWS::on_resolve,
            shared_from_this(),
            std::placeholders::_1,
            std::placeholders::_2));
}

void AlpacaServiceWS::on_resolve(boost::system::error_code ec, tcp::resolver::results_type results){
    if(ec)
        return fail(ec, "resolve");
    std::cout << "resolve" << std::endl;
    // Make the connection on the IP address we get from a lookup
    boost::asio::async_connect(
        ws_.next_layer(),
        results.begin(),
        results.end(),
        std::bind(
            &AlpacaServiceWS::on_connect,
            shared_from_this(),
            std::placeholders::_1));
}

void AlpacaServiceWS::on_connect(boost::system::error_code ec){
        if(ec)
            return fail(ec, "connect");
        std::cout << "connect" << std::endl;

        // Perform the websocket handshake
        ws_.async_handshake(host_, "/stream",
            std::bind(
                &AlpacaServiceWS::on_handshake,
                shared_from_this(),
                std::placeholders::_1));
    }

void AlpacaServiceWS::on_handshake(boost::system::error_code ec)
    {
        if(ec)
            return fail(ec, "handshake");
        std::cout << "hs" << std::endl;

        // Send the message
        ws_.async_write(
            boost::asio::buffer(data_.dump()),
            std::bind(
                &AlpacaServiceWS::on_write,
                shared_from_this(),
                std::placeholders::_1,
                std::placeholders::_2));
    }

void AlpacaServiceWS::on_write(boost::system::error_code ec, std::size_t bytes_transferred){
	boost::ignore_unused(bytes_transferred);

	if(ec)
		return fail(ec, "write");
	std::cout << "write" << std::endl;

	// Read a message into our buffer
	ws_.async_read(
		buffer_,
		std::bind(
			&AlpacaServiceWS::on_read,
			shared_from_this(),
			std::placeholders::_1,
			std::placeholders::_2));
}

void AlpacaServiceWS::on_read(
	boost::system::error_code ec,
	std::size_t bytes_transferred){
	boost::ignore_unused(bytes_transferred);

	if(ec)
		return fail(ec, "read");

	// Close the WebSocket connection
	ws_.async_close(websocket::close_code::normal,
		std::bind(
			&AlpacaServiceWS::on_close,
			shared_from_this(),
			std::placeholders::_1));
}

void AlpacaServiceWS::on_close(boost::system::error_code ec){
	if(ec)
		return fail(ec, "close");

	// If we get here then the connection is closed gracefully

	// The buffers() function helps print a ConstBufferSequence
	std::cout << buffers_to_string(buffer_.data()) << std::endl;
}

