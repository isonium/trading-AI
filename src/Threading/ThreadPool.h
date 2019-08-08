/*
 * ThreadPool.h
 *
 *  Created on: Aug 8, 2019
 *      Author: sakex
 */

#ifndef THREADING_THREADPOOL_H_
#define THREADING_THREADPOOL_H_

#include <queue>
#include <functional>
#include <thread>
#include <iostream>
#include <atomic>

namespace Threading {

class ThreadPool {
public:
	explicit ThreadPool(int const & max_threads);
	~ThreadPool();

	void add_task(std::function<void()> & func);
	void run();

private:
	int max_threads;
	std::atomic_int working_threads; // Needs to be thread safe
	bool locked = false;
	std::queue<std::function<void()>> queue;

	void thread_callback();
};

} /* namespace Threading */

#endif /* THREADING_THREADPOOL_H_ */
