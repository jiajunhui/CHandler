// CHandler.cpp: 定义应用程序的入口点。
//

#include<iostream>
#include<thread>
#include<chrono>
#include "Handler.h"

using namespace std;

void handleMessage(Message& msg) {
	cout << "handleMessage:what=" << msg.what << ",arg1=" << msg.arg1 << ",arg2=" << msg.arg2 << endl;
}

void printNow() {
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto value = now_ms.time_since_epoch().count();
	cout << "now_time_ms=" << value << endl;
}

int main()
{
	Handler handler(handleMessage);
	cout << "start=>" << endl;
	printNow();
	handler.sendEmptyMessageDelay(666, 1000);
	std::this_thread::sleep_for(std::chrono::seconds(1));

	printNow();
	handler.postDelay([] {
		cout << "post delay invoke..." << endl;
		}, 1000);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	printNow();
	handler.postAtTime([] {
		cout << "post at time invoke..." << endl;
		}, std::chrono::system_clock::now() + std::chrono::microseconds(1000));

	int i = 0;
	while (true)
	{
		i += 1;
		if (i % 3 == 0) {
			handler.post([=] {
				cout << "post invoke..." << i << endl;;
				});
		} else if (i % 3 == 1) {
			handler.sendEmptyMessage(i + 10);
		} else if (i % 3 == 2) {
			Message message(i, i + 100, i + 200);
			handler.sendMessage(message);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	
	return 0;
}
