#pragma once
#include "IThreadable.h"
#include <boost/thread.hpp>
#include <deque>

namespace TrudyTheCrawler
{

typedef unsigned int uint;
	
class ThreadPool
{	
	public:
		ThreadPool( uint poolSize = 10 );
		~ThreadPool( void );
	
		void						start( void );

	private:
		void						submitTask( IThreadable* threadable ); //enques task for execution (worker will be deleted after execution)
		IThreadable*				getTask(); //waits for signal to return task
		unsigned int				threads_main( ThreadPool* threadPool );

		std::deque<IThreadable*>	_taskQueue;
		std::vector<boost::thread>	_threadList;
		uint						_threadCount;
		boost::mutex				_mutex;
		boost::condition_variable	_condition;
};

};