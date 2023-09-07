#ifndef CHANDLER_HANDLER_H
#define CHANDLER_HANDLER_H

#include<functional>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<chrono>
#include "MessageQueue.h"
#include "Looper.h"

class Message;
typedef std::function<void(Message&)> HandleCallback;

class Handler {
public:
	Handler(HandleCallback callback) :_callback(callback) {

	}
	void post(Runnable r);

	void postAtTime(Runnable r, TimePoint upTimeMillis);

	void postDelay(Runnable r, long delayMillis);

	void sendMessage(Message& msg);

	void sendMessageAtTime(Message& msg, TimePoint upTimeMillis);

	void sendMessageDelay(Message& msg, long delayMillis);

	void sendEmptyMessage(int what);

	void sendEmptyMessageAtTime(int what, TimePoint upTimeMillis);

	void sendEmptyMessageDelay(int what, long delayMillis);

	void removeMessages(int what);

	bool operator==(const Handler& handler) const {
		return this == &handler;
	}

public:
	HandleCallback _callback;

private:
	Looper _looper;

};

#endif // !CHANDLER_HANDLER_H

