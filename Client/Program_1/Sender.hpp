#ifndef _IF_SENDER_INCLUDE
#define _IF_SENDER_INCLUDE
#include<iostream>
#include<sstream>
#include<condition_variable>
#include<vector>
#include<atomic>
#include<cctype>
#include"ThException.hpp"
#include"Client.hpp"

// class "Thread 2"
class Sender {
private:
	Client client;
	std::shared_ptr<std::mutex> mutexW;
	std::shared_ptr<std::condition_variable> data_cond;
	float timeToWait = 30.f; // time for reconnect

	int calcSum(std::string& str);

	bool connect_until(); // try to connect before 30 seconds have passed
public:
	Sender(const std::shared_ptr<std::mutex>& mutex, const std::shared_ptr<std::condition_variable>& cond);

	void run(std::vector<std::string>& buffer, std::atomic_bool& isReadable);
};

#endif // _IF_SENDER_INCLUDE