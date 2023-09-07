#include "Looper.h"
#include "MessageQueue.h"

Looper::Looper()
{
	_loop_thread = std::thread(&Looper::loop, this);
	_message_queue_ptr = std::make_shared<MessageQueue>();
}

Looper::~Looper()
{
	_loop_thread.join();
	_message_queue_ptr->removeAllMessages();
}

void Looper::loop()
{
	while (true) {
		Message msg;
		if (_message_queue_ptr->next(msg)) {
			if (msg.callback) {
				msg.callback();
			} else {
				msg.target->_callback(msg);
			}
			
		}
	}
}
