#ifndef CHANDLER_MESSAGE_H
#define CHANDLER_MESSAGE_H

#include<functional>
#include<chrono>

typedef std::function<void()> Runnable;
typedef std::chrono::system_clock::time_point TimePoint;

class Handler;
class Message {
public:
	int what;
	int arg1;
	int arg2;
	TimePoint when;
	void* obj;
	Handler* target;
	Runnable callback;

public:
	Message();

	explicit Message(int what);

	explicit Message(int what, int arg1);

	explicit Message(int what, int arg1, int arg2);

	explicit Message(int what, int arg1, int arg2, void* obj);

	explicit Message(int what, int arg1, int arg2, void* obj, long updateTimeMillis);

	void setWhen(long delayMillis);

	void setTarget(Handler* handler);

	void setCallback(Runnable callback);
	
	virtual ~Message();

	bool operator==(int what) const {
		return this->what == what;
	}

	bool operator==(const Message& msg) const {
		return this->what == msg.what && this->target != nullptr && msg.target != nullptr;
	}

	bool operator>(const Message& msg) const {
		return this->when > msg.when;
	}

	bool operator<(const Message& msg) const {
		return this->when < msg.when;
	}
};



#endif // !CHANDLER_MESSAGE_H
