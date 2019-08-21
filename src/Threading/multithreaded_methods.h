/*
 * multithreaded_methods.h
 *
 *  Created on: Aug 10, 2019
 *      Author: sakex
 */

#ifndef THREADING_MULTITHREADED_METHODS_H_
#define THREADING_MULTITHREADED_METHODS_H_

#include <thread>
#include <mutex>

namespace Threading {

template<typename Iterable, typename Callable>
static void forEach(Iterable _begin, Iterable _end, Callable & cb,
		int max_threads = std::thread::hardware_concurrency()) {
	int size = _end - _begin;
	if (!size)
		return;
	max_threads--;
	std::mutex locker;
	std::vector<std::thread> threads;
	int * counter = new int(0);
	auto lambda = [_begin, _end, counter, &cb, &locker]() -> void {
		int & _count = *counter;
		while(true) {
			locker.lock();
			int temp = _count;
			_count++;
			locker.unlock();
			if(temp + _begin < _end)
				cb(*(temp + _begin));
			else
				break;
		}
	};
	for (int it = 0; it < max_threads; ++it)
		threads.push_back(std::thread(lambda));
	lambda(); // run on main thread
	for (std::thread & thread : threads) {
		thread.join();
	}
	delete counter;
}
}
#endif /* THREADING_MULTITHREADED_METHODS_H_ */
