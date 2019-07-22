/*
 * Event.h
 *
 *  Created on: Apr 6, 2019
 *      Author: sakex
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <boost/function.hpp>

#include <vector>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

using namespace std;

constexpr void * NULL_PTR = NULL;

template <class T>
class Event {
public:
	Event(){};
	virtual ~Event(){};

	void addListener(void (* function)(T)){
		listeners.push_back(function);
	}

	void addListener(boost::function<void (T)> function){
		boost_listeners.push_back(function);
	}

	void emit() const{
		T temp = NULL;
		unsigned it;
		for(it = 0; it < listeners.size(); ++it){
			listeners[it](temp);
		}
		for(it = 0; it < boost_listeners.size(); ++it){
			listeners[it](temp);
		}
	}

	void emit(T data) const {
		unsigned it;
		for(it = 0; it < listeners.size(); ++it){
			listeners[it](data);
		}
		for(it = 0; it < boost_listeners.size(); ++it){
			boost_listeners[it](data);
		}
	}

private:
	std::vector<void (*)(T)> listeners;
	std::vector<boost::function<void (T)>> boost_listeners;
};

#endif /* EVENT_H_ */
