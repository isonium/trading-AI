/*
 * Event.h
 *
 *  Created on: Apr 6, 2019
 *      Author: sakex
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <vector>

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

	void emit() const{
		for(unsigned it = 0; it < listeners.size(); ++it){
			listeners[it](NULL_PTR);
		}
	}

	void emit(T data) const {
		for(unsigned it = 0; it < listeners.size(); ++it){
			listeners[it](data);
		}
	}

private:
	vector<void (*)(T)> listeners;
};

#endif /* EVENT_H_ */
