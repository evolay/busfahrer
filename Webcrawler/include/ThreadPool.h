#pragma once
#include "IThreadable.h"
#include <boost/thread.hpp>
#include <deque>
typedef unsigned int uint;

namespace RudyTheCrawler
{
	
class ThreadPool
{	
	public:
		ThreadPool( uint poolSize = 10 );
		~ThreadPool( void );
	
		void						submitTask( IThreadable* threadable ); //enques task for execution (worker will be deleted after execution)
		bool						getTasksFinished( int restIntervalMs ); //doublecheck of the queuesize in a given interval

	private:
		IThreadable*				getTask(); //returns task if queue != empty, else waiting for notification
		unsigned int				threads_main( ThreadPool* threadPool );

		std::deque<IThreadable*>	_taskQueue;
		std::vector<boost::thread*>	_threadList;
		uint						_threadCount;
		boost::mutex				_mutex;
		boost::condition_variable	_taskCondition;
};

};
