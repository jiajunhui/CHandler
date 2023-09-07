#ifndef CHANDLER_LOOPER_H
#define CHANDLER_LOOPER_H

#include<thread>
#include<vector>
#include<memory>

class MessageQueue;
using MessageQueuePtr = std::shared_ptr<MessageQueue>;

class Looper {
public:
	Looper();
	virtual ~Looper();

public:
	MessageQueuePtr _message_queue_ptr;

private:
	std::thread _loop_thread;
	
	void loop();
};

#endif // !CHANDLER_LOOPER_H
