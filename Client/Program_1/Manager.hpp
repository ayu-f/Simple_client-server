#ifndef _IF_MANAGER_INCLUDE
#define _IF_MANAGER_INCLUDE
#include <condition_variable>
#include <string.h>
#include <thread>
#include"ThException.hpp"
#include "Reader.hpp"
#include "Sender.hpp"


class Manager {
private:
	std::vector<std::string> buffer;
	std::shared_ptr<std::mutex> mutex;
	std::shared_ptr<std::condition_variable> data_cond;
	std::atomic_bool isReadable;

public:
	Manager() {
		mutex = std::make_shared<std::mutex>();
		data_cond = std::make_shared<std::condition_variable>();
		isReadable = true;
	}

	void start() {
		std::cout << "Enter a non-negative integer:" << std::endl;

		Reader reader(mutex, data_cond);
		Sender sender(mutex, data_cond);
		std::thread inp(&Reader::run, &reader, std::ref(buffer), std::ref(isReadable));
		std::thread out(&Sender::run, &sender, std::ref(buffer), std::ref(isReadable));
		inp.join();
		out.join();
	}


};

#endif //_IF_MANAGER_INCLUDE
