#include "MessageQueue.h"
#include<iostream>

int MessageQueue::next(Message& message)
{
	std::unique_lock<std::mutex> lock(_mutex);
	if (_message_queue.empty()) {
		_condition.wait(lock, [=] {return !_message_queue.empty(); });
	} else {
		_condition.wait_until(lock, _message_queue.back().when, [=] {return _message_queue.empty(); });
	}
	if (!_message_queue.empty()) {
		Message msg = _message_queue.back();
		auto now = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
		auto when = std::chrono::time_point_cast<std::chrono::microseconds>(msg.when);
		auto delay = now.time_since_epoch().count() - when.time_since_epoch().count();
		if (delay >= 0) {
			message = std::move(msg);
			_message_queue.pop_back();
			return 1;
		}
	}
	return 0;
}

bool MessageQueue::enqueueMessage(Message& msg)
{
	std::unique_lock<std::mutex> lock(_mutex);
	_message_queue.push_back(msg);
	std::sort(_message_queue.begin(), _message_queue.end());
	_condition.notify_one();
	return true;
}

void MessageQueue::removeMessage(Handler& handler, int what, void* obj)
{
	std::unique_lock<std::mutex> lock(_mutex);
	auto it = std::find(_message_queue.begin(), _message_queue.end(), what);
	if (it != _message_queue.end() && *(it->target) == handler && (obj==nullptr || obj == it->obj)) {
		_message_queue.erase(it);
	}
}

void MessageQueue::removeAllMessages()
{
	std::unique_lock<std::mutex> lock(_mutex);
	_message_queue.clear();
	_condition.notify_all();
}
