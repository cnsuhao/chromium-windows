#include "StdAfx.h"
#include "Backend.h"

CBackend::CBackend(void)
{
	
	InitializeThread();
}

CBackend::~CBackend(void)
{
	if(thread_->IsRunning())
	{
		scoped_ptr<base::Thread> Nil;
		thread_->Stop();
		thread_.swap(Nil);
	}
	
}

void CBackend::InitializeThread()
{
	scoped_ptr<base::Thread> thread(new base::Thread("Backend"));
	base::Thread::Options options;
	options.message_loop_type = MessageLoop::TYPE_IO;
	bool thread_result = thread->StartWithOptions(options);
	DCHECK(thread_result);
	thread_.swap(thread);
}

void CBackend::PostTask
	( const tracked_objects::Location& from_here
	, const base::Closure& task
	, const int kMenuTimerDelay
	) 
{
	// 3ÃëÑÓ³ÙÖ´ÐÐ
	//static const int kMenuTimerDelay = 3000;
	return thread_->message_loop()->PostDelayedTask
		( from_here
		, task
		, kMenuTimerDelay
		);
}
