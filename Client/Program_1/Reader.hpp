#ifndef _IF_READER_INCLUDE
#define _IF_READER_INCLUDE
#include<iostream>
#include<condition_variable>
#include<cctype>
#include<vector>
#include<algorithm>
#include<memory>
#include<atomic>
#include<mutex>
#include"ThException.hpp"

// class "Thread 1"
class Reader {
private:
	std::string inputStr;
	unsigned int maxLength = 64;
	std::shared_ptr<std::mutex> mutexR;
	std::shared_ptr<std::condition_variable> data_cond;

	bool IsStrOnlyNumbers(std::string& str);

	void read();

	std::string parseStrToBuffer();
public:
	Reader(const std::shared_ptr<std::mutex>&mutex, const std::shared_ptr<std::condition_variable>&cond);

	void run(std::vector<std::string>& buffer, std::atomic_bool& isReadable);
};

#endif // _IF_READER_INCLUDE