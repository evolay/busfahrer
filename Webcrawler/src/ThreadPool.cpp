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
		if(_abort) {
			//std::cout << "Quitting Thread\n";
			return 0;
		}
		if(_task == NULL) continue;
		_task->run();_taskCondition.notify_all();
		delete _task;
	}
	return 0;
}

//-----------------------------------------------------------------

ThreadPool::ThreadPool(uint poolSize)
{
	_abort = false;

	_ActiveTaskCount = 0;
	uint _size;
	if(poolSize <= 0)_size = 10;
	else _threadCount = poolSize;
	
	for(uint i=0; i < _threadCount; i++)
		_threadList.push_back( new boost::thread( boost::bind(&ThreadPool::threads_main, this, this)) );
}

ThreadPool::~ThreadPool(void)
{
	_abort = true;
	for(uint i=0; i < _threadCount; i++)
		delete _threadList[i];
	_threadList.empty();
	_taskCondition.notify_all();
}

void ThreadPool::submitTask(IThreadable* threadable)
{
	_mutex.lock();
		//std::cout << "ThreadPool::submitTask -> submitting Task..." << std::endl;
		_taskQueue.push_back( threadable );
		_taskCondition.notify_one();
		_ActiveTaskCount++;
	_mutex.unlock();
}

void ThreadPool::decreaseTaskCount()
{
	_mutex.lock();
		_ActiveTaskCount--;
	_mutex.unlock();
}

IThreadable* ThreadPool::getTask()
{
	boost::unique_lock<boost::mutex> _lock( _mutex );
	IThreadable* _tmp = NULL;

	if( !_taskQueue.size() )
		_taskCondition.wait( _lock ); //when thread gets fired -> _lock = locked
	if(_taskQueue.size() > 0 )
	{
		_tmp = _taskQueue[0];
		_taskQueue.erase( _taskQueue.begin() );
	}
	_lock.unlock();
	return _tmp;
}

bool ThreadPool::getTasksFinished( int restIntervalMs )
{
	/*
	bool abort = true;
	for(int i=0;i<10;i++) {
		#ifdef _WIN32
			Sleep( restIntervalMs ); //Windows
		#else
			sleep( restIntervalMs / 1000 ); //Unix
		#endif
		if(_taskQueue.size() > 0)
			abort = false;
	}*/

	#ifdef _WIN32
		Sleep( restIntervalMs ); //Windows
	#else
		sleep( restIntervalMs / 1000 ); //Unix
	#endif
std::cout << "Tasks running: " << _ActiveTaskCount << std::endl;
 	if(_ActiveTaskCount > 0)
		return false;
	else
		return true;
}
