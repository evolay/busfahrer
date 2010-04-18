#include "ThreadPool.h"
#include <iostream>
#ifdef _WIN32
	#include <windows.h>
#endif

using namespace RudyTheCrawler;

unsigned int ThreadPool::threads_main( ThreadPool* threadPool ) {
	
	while(true)
	{ 
		IThreadable* _task = threadPool->getTask();
		//std::cout << "Thread: " << boost::this_thread::get_id() << " - is in working progress..." << std::endl;
		if(_task == NULL) continue;
		_task->run();
		delete _task;
	}
	return 0;
}

//-----------------------------------------------------------------

ThreadPool::ThreadPool(uint poolSize)
{
	uint _size;
	if(poolSize <= 0)_size = 10;
	else _threadCount = poolSize;
	
	for(uint i=0; i < _threadCount; i++)
		_threadList.push_back( new boost::thread( boost::bind(&ThreadPool::threads_main, this, this)) );
}

ThreadPool::~ThreadPool(void)
{
	for(uint i=0; i < _threadCount; i++)
		delete _threadList[i];
	_threadList.empty();
}

void ThreadPool::submitTask(IThreadable* threadable)
{
	_mutex.lock();
		//std::cout << "ThreadPool::submitTask -> submitting Task..." << std::endl;
		_taskQueue.push_back( threadable );
		_taskCondition.notify_one();
	_mutex.unlock();
}

IThreadable* ThreadPool::getTask()
{
	boost::unique_lock<boost::mutex> _lock( _mutex );
	IThreadable* _tmp = NULL;

	if( !_taskQueue.size() )
		_taskCondition.wait( _lock ); //when thread gets fired -> _lock = locked
	if(_taskQueue.size() )
	{
		_tmp = _taskQueue[0];
		_taskQueue.erase( _taskQueue.begin() );
	}
	_lock.unlock();
	return _tmp;
}

bool ThreadPool::getTasksFinished( int restIntervalMs )
{
	bool abort = true;
	for(int i=0;i<10;i++) {
		#ifdef _WIN32
			Sleep( restIntervalMs ); //Windows
		#else
			sleep( restIntervalMs / 1000 ); //Unix
		#endif
		if(_taskQueue.size() > 0)
			abort = false;
	}

	return abort;
}
