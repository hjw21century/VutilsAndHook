﻿/*
Copyright (c) 2013, Tolga HOŞGÖR
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.
*/

#include <algorithm>

#include "../include/threadpool11/threadpool11.h"

namespace threadpool11
{
	
Pool::Pool(WorkerCountType const& workerCount) :
	activeWorkerCount(0),
	areAllReallyFinished(false)
{
	spawnWorkers(workerCount);
}
	
Pool::~Pool()
{
	joinAll();
}

void Pool::postWork(Worker::WorkType work)
{
	{
		std::lock_guard<std::mutex> lock(workerContainerMutex);
		
		if(activeWorkerCount < workers.size())
		{
			for(auto& it : workers)
			{
				if(it.status == Worker::Status::DEACTIVE)
				{
					++activeWorkerCount;
					it.setWork(std::move(work));
					return;
				}
			}
		}
	}
	
	enqueuedWorkMutex.lock();
	enqueuedWork.emplace_back(std::move(work));
	enqueuedWorkMutex.unlock();
}

void Pool::waitAll()
{
	workerContainerMutex.lock();
	WorkerCountType size = activeWorkerCount;
	workerContainerMutex.unlock();
	std::unique_lock<std::mutex> lock(notifyAllFinishedMutex);
	if(size)
	{
		notifyAllFinished.wait(lock, [this](){ return areAllReallyFinished; });
		areAllReallyFinished = false;
	}
}

void Pool::joinAll()
{
	for(auto& it : workers)
	{
		it.terminate = true;
		std::unique_lock<std::mutex> lock(it.activatorMutex);
		it.isWorkReallyPosted = true;
		it.activator.notify_one();
		lock.unlock();
		it.thread.join();
	}
	workers.clear();
	//No mutex here since no threads left.
	enqueuedWork.resize(0);
}

Pool::WorkerCountType Pool::getWorkQueueCount() const
{
	std::lock_guard<std::mutex> l(enqueuedWorkMutex);	
	return enqueuedWork.size();
}

Pool::WorkerCountType Pool::getWorkerCount() const
{
	std::lock_guard<std::mutex> l(workerContainerMutex);
  return workers.size();
}

Pool::WorkerCountType Pool::getActiveWorkerCount() const
{
	std::lock_guard<std::mutex> l(workerContainerMutex);
	return activeWorkerCount;
}

Pool::WorkerCountType Pool::getInactiveWorkerCount() const
{
	std::lock_guard<std::mutex> l(workerContainerMutex);
	return (workers.size() - activeWorkerCount);
}

void Pool::increaseWorkerCountBy(WorkerCountType const& n)
{
	std::lock_guard<std::mutex> l(workerContainerMutex);
	spawnWorkers(n);
}

Pool::WorkerCountType Pool::decreaseWorkerCountBy(WorkerCountType const& n)
{
	std::lock_guard<std::mutex> l(workerContainerMutex);
	WorkerCountType i = std::min(n, static_cast<Pool::WorkerCountType>(workers.size()));
	while(i > 0)
	{
    if(workers.back().status != Worker::Status::DEACTIVE)
      break;
    workers.back().terminate = true;
    workers.back().isWorkReallyPosted = true;
    workers.back().activator.notify_one();
    workers.back().thread.join();
    workers.pop_back();
    --i;
	}
	return n - i;
}

void Pool::spawnWorkers(WorkerCountType const& n)
{
	//'OR' makes sure the case where one of the variables is zero, is valid.
	assert(static_cast<WorkerCountType>(workers.size() + n) > n || static_cast<WorkerCountType>(workers.size() + n) > workers.size());
	for(WorkerCountType i = 0; i < n; ++i)
	{
		workers.emplace_back(this);
		std::unique_lock<std::mutex> lock(workers.back().initMutex);
		if(workers.back().isReallyInitialized == 0)
			workers.back().initializer.wait(lock, [this](){ return workers.back().isReallyInitialized; });
	}
}

}
