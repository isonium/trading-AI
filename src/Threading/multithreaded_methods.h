/*
 * multithreaded_methods.h
 *
 *  Created on: Aug 10, 2019
 *      Author: sakex
 */

#ifndef THREADING_MULTITHREADED_METHODS_H_
#define THREADING_MULTITHREADED_METHODS_H_

#include <thread>

namespace Threading {

template<typename Iterable, typename Callable>
static void forEach(Iterable _begin, Iterable _end, Callable & cb,
		int max_threads = std::thread::hardware_concurrency()) {
	int size = _end - _begin;
	if (!size)
		return;
	max_threads--;
	std::vector<std::thread> threads;
	int batch_size = size / max_threads;
	int modulo = size % max_threads;
	Iterable it;
	for (it = _begin; it != _end - modulo; it += batch_size) {
		auto lambda = [it, &cb, &batch_size]() -> void {
			for(int iter = 0; iter != batch_size; ++iter) {
				cb(*(it + iter));
			}
		};
		threads.push_back(std::thread(lambda));
	}
	for (Iterable iter = it; iter != _end; ++iter) {
		cb(*iter);
	} // run on main thread
	for (std::thread & thread : threads) {
		thread.join();
	}
}

}
#endif /* THREADING_MULTITHREADED_METHODS_H_ */
