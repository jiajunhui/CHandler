#include "Handler.h"
#include<thread>

void Handler::post(Runnable r)
{
	Message message;
	message.callback = r;
	sendMessage(message);
}

void Handler::postAtTime(Runnable r, TimePoint upTimeMillis)
{
	Message message;
	message.callback = r;
	sendMessageAtTime(message, upTimeMillis);
}

void Handler::postDelay(Runnable r, long delayMillis)
{
	Message message;
	message.callback = r;
	sendMessageDelay(message, delayMillis);
}

void Handler::sendMessage(Message& msg)
{
	msg.setTarget(this);
	_looper._message_queue_ptr->enqueueMessage(msg);
}

void Handler::sendMessageAtTime(Message& msg, TimePoint upTimeMillis)
{
	msg.when = upTimeMillis;
	msg.setTarget(this);
	_looper._message_queue_ptr->enqueueMessage(msg);
}

void Handler::sendMessageDelay(Message& msg, long delayMillis)
{
	msg.when = std::chrono::system_clock::now() + std::chrono::microseconds(delayMillis);
	msg.setTarget(this);
	_looper._message_queue_ptr->enqueueMessage(msg);
}

void Handler::sendEmptyMessage(int what)
{
	sendEmptyMessageDelay(what, 0);
}

void Handler::sendEmptyMessageAtTime(int what, TimePoint upTimeMillis)
{
	Message message(what);
	message.when = upTimeMillis;
	message.setTarget(this);
	_looper._message_queue_ptr->enqueueMessage(message);
}

void Handler::sendEmptyMessageDelay(int what, long delayMillis)
{
	Message message(what);
	message.setWhen(delayMillis);
	message.setTarget(this);
	_looper._message_queue_ptr->enqueueMessage(message);
}

void Handler::removeMessages(int what)
{
	_looper._message_queue_ptr->removeMessage(*this, what, nullptr);
}
