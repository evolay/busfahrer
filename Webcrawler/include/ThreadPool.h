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
		void						decreaseTaskCount();
boost::mutex					_mutex;

	private:
		IThreadable*				getTask(); //returns task if queue != empty, else waiting for notification
		unsigned int				threads_main( ThreadPool* threadPool );

		std::deque<IThreadable*>	_taskQueue;
		std::vector<boost::thread*>	_threadList;
		uint						_threadCount;
		boost::condition_variable	_taskCondition;
		unsigned int				_ActiveTaskCount;
		bool 				_abort;
};

};
