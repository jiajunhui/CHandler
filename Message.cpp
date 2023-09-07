#include "Message.h"

Message::Message():Message(0)
{
}

Message::Message(int what):Message(what, 0)
{
}

Message::Message(int what, int arg1):Message(what, arg1, 0)
{
}

Message::Message(int what, int arg1, int arg2):Message(what, arg1, arg2, nullptr)
{
}

Message::Message(int what, int arg1, int arg2, void* obj):Message(what, arg1, arg2, obj, 0)
{
	
}

Message::Message(int what, int arg1, int arg2, void* obj, long updateTimeMillis):what(what), arg1(arg1), arg2(arg2), obj(obj), target(nullptr)
{
	this->when = std::chrono::system_clock::now() + std::chrono::microseconds(updateTimeMillis);
	this->callback = nullptr;
}

void Message::setWhen(long delayMillis)
{
	this->when = std::chrono::system_clock::now() + std::chrono::microseconds(delayMillis);
}

void Message::setTarget(Handler* handler)
{
	this->target = handler;
}

void Message::setCallback(Runnable callback)
{
	this->callback = callback;
}

Message::~Message() = default;
