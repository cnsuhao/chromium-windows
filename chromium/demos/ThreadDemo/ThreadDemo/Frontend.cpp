#include "StdAfx.h"
#include "Frontend.h"
#include "base/threading/thread.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/message_loop.h"
#include "base/threading/non_thread_safe.h"
#include "chrome/browser/cancelable_request.h"
#include "base/callback_forward.h"

CFrontend::CFrontend(void)
: backend_( NULL)
{
	backend_ = new CBackend;
	InitializeThread();
}

CFrontend::~CFrontend(void)
{
	
	//if(thread_->IsRunning())
	//{
	//	thread_->Stop();
	//	scoped_ptr<base::Thread> Nil;
	//	thread_.swap(Nil);
	//	//scoped_ptr<base::Thread> Nil;
	//	//
	//	//thread_.swap(Nil);
	//}
	//thread_.release();
	if(NULL != backend_)
		delete backend_;
	thread_.reset();
}

void CFrontend::InitializeThread()
{
	scoped_ptr<base::Thread> thread(new base::Thread("Frontend"));
	base::Thread::Options options;
	options.message_loop_type = MessageLoop::TYPE_IO;
	bool thread_result = thread->StartWithOptions(options);
	DCHECK(thread_result);
	thread_.swap(thread);

}

void CFrontend::DoTask1(const std::wstring& strText)
{
	AfxMessageBox(strText.c_str());
}
void CFrontend::DoRequest1()
{
	if(NULL != backend_)
	{
		std::wstring strInfo = _T("您好asdfasfasdfasdfasdf");
		static const int kMenuTimerDelay = 0000;
		backend_->PostTask
					( FROM_HERE
					, base::Bind
						( &CFrontend::DoTask1
						//, base::Unretained(this)
						, this
						//, make_scoped_refptr(request)
						, strInfo
						)
					, kMenuTimerDelay
					);
	}
}


void CFrontend::RequestComplete(
							   CancelableRequestProvider::Handle handle
							   , scoped_refptr<RequestResult> data)
{
	//AfxMessageBox(_T("执行回调函数"));
	AfxMessageBox(data->info.c_str());
}

void CFrontend::DoTask2( scoped_refptr<CFrontend::StartRequestRequest> request
			  , const std::wstring& strText
			  )
{
	if(request->canceled())
		return;
	//some_method_factory_.InvalidateWeakPtrs();

	AfxMessageBox(strText.c_str());
	
	request->value->info = _T("返回信息");
	request->ForwardResult(request->handle(), request->value);

}

CancelableRequestProvider::Handle 
CFrontend::StartRequest
	( CancelableRequestConsumer* consumer
	, const RequestCallback& callback
	)
{
	//static const int kMenuTimerDelay = 0;
	StartRequestRequest* request = new StartRequestRequest(callback);
	request->value = new RequestResult;
	AddRequest(request, consumer);

	backend_->PostTask
		( FROM_HERE
		, base::Bind
			( &CFrontend::DoTask2
			, this
			, make_scoped_refptr(request)
			, _T("您好")
			)
		, 0
		);
	return request->handle();
}

void CFrontend::DoRequest2()
{
	CancelableRequestProvider::Handle handle = StartRequest
		( &callback_consumer_
		, base::Bind
			( &CFrontend::RequestComplete
			, this
			)
		);//*/
}