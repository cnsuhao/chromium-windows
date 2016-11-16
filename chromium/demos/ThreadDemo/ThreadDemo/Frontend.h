#pragma once
#include "base/threading/thread.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/message_loop.h"
#include "base/threading/non_thread_safe.h"
#include "chrome/browser/cancelable_request.h"
#include "base/callback_forward.h"


#include "base/threading/thread.h"
#include "chrome/browser/cancelable_request.h"
#include "Backend.h"

class RequestResult
	: public base::RefCountedThreadSafe<RequestResult>
{
public:
	std::wstring	info;
};

class CFrontend
	: public base::RefCountedThreadSafe<CFrontend>
	, public CancelableRequestProvider
{
	typedef base::Callback<void(Handle,scoped_refptr<RequestResult>) > RequestCallback;
	typedef CancelableRequest1<CFrontend::RequestCallback,scoped_refptr<RequestResult> > StartRequestRequest;
public:
	CFrontend(void);
	~CFrontend(void);
	void InitializeThread();
	void DoTask1(const std::wstring& strText);
	void DoRequest1();
	void RequestComplete(CancelableRequestProvider::Handle handle, scoped_refptr<RequestResult> data);
	//void DoRequest( scoped_refptr<Frontend::StartRequestRequest> request
	//			  , const std::wstring& strText
	//			  );
	void DoTask2( scoped_refptr<CFrontend::StartRequestRequest> request
				  , const std::wstring& strText
				  );

	void DoRequest2();
	CancelableRequestProvider::Handle 
		StartRequest( CancelableRequestConsumer* consumer
		, const RequestCallback& callback
		);
public:
	scoped_ptr<base::Thread> thread_;
	CBackend * backend_;
	CancelableRequestConsumer callback_consumer_;
};
