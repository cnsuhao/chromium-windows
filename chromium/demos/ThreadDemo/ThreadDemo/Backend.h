#pragma once

#include "base/threading/thread.h"

class CBackend
	//: public base::RefCountedThreadSafe<CBackend>
{
public:
	CBackend(void);
	~CBackend(void);
	void InitializeThread();
	void PostTask
		( const tracked_objects::Location& from_here
		, const base::Closure& task
		, const int kMenuTimerDelay
		);
public:
	scoped_ptr<base::Thread> thread_;
};
