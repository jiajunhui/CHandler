#ifndef CHANDLER_MESSAGEQUEUE_H
#define CHANDLER_MESSAGEQUEUE_H

#include<vector>
#include<mutex>
#include<condition_variable>
#include "Message.h"
#include "Handler.h"

class MessageQueue {
public:
	MessageQueue() {
	}

public:
	int next(Message& message);

	bool enqueueMessage(Message& msg);

	void removeMessage(Handler& handler, int what, void* obj);
	
	void removeAllMessages();

private:
	std::vector<Message> _message_queue;
	std::mutex _mutex;
	std::condition_variable _condition;

};

#endif // !CHANDLER_MESSAGEQUEUE_H
