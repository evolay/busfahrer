#include "ThreadPool.h"
#include <iostream>

using namespace TrudyTheCrawler;

unsigned int ThreadPool::threads_main( ThreadPool* threadPool ) {
	
	while(true)
	{ 
		std::cout << "balsdf" << std::endl;
	/*
		IThreadable* _task = _threadPool->getTask();
		if(_task == NULL) continue;
		_task->run();
		delete _task;
	*/
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
		_threadList[i] = boost::thread( boost::bind(&ThreadPool::threads_main, this));

}

ThreadPool::~ThreadPool(void)
{
	uint _size = _taskQueue.size();
	for(uint i=0; i<_size; i++)
		delete _taskQueue[i];
	_taskQueue.empty();
}

void ThreadPool::submitTask(IThreadable* threadable)
{
	boost::mutex::scoped_lock( _mutex );
	std::cout << "ThreadPool::submitTask -> submitting Task..." << std::endl;
	_taskQueue.push_back( threadable );
	_condition.notify_one();
}

IThreadable* ThreadPool::getTask()
{
/*	_tasksAvailable.wait();
	_queueLock.lock();
	IThreadable* _tmp = NULL;
	int size = 0;
	size = _taskQueue.size();
	if(_taskQueue.size() > 0)
	{
		_tmp = _taskQueue[0];
		_taskQueue.erase( _taskQueue.begin() );
	}
	_queueLock.unlock();
	return _tmp;
*/
	return NULL;
}

void ThreadPool::start( void )
{
}
