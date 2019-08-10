/*
 * multithreaded_methods.h
 *
 *  Created on: Aug 10, 2019
 *      Author: sakex
 */

#ifndef THREADING_MULTITHREADED_METHODS_H_
#define THREADING_MULTITHREADED_METHODS_H_

#include "ThreadPool.h"

namespace Threading {

template<typename Iterable, typename Callable>
static void forEach(Iterable _begin, Iterable _end, Callable & cb,
		int max_threads = 8) {
	int size = _end - _begin;
	if (!size)
		return;
	max_threads--;
	ThreadPool tp(max_threads);
	int batch_size = size / max_threads;
	int modulo = size % max_threads;
	Iterable it;
	for (it = _begin; it != _end - modulo; it += batch_size) {
		std::function<void()> && lambda = [it, &cb, &batch_size]() -> void {
			for(int iter = 0; iter != batch_size; ++iter) {
				cb(*(it + iter));
			}
		};
		std::function<void()> func = lambda;
		tp.add_task(lambda);
	}
	std::function<void()> && lambda = [it, &cb, &_end]() -> void {
		for(Iterable iter = it; iter != _end; ++iter) {
			cb(*iter);
		}
	};
	std::function<void()> func = lambda;
	tp.add_task(lambda);
	tp.run();
}

}
#endif /* THREADING_MULTITHREADED_METHODS_H_ */
