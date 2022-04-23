#include"Reader.hpp"

bool Reader::IsStrOnlyNumbers(std::string& str) {
	for (auto& c : str) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}
Reader::Reader(const std::shared_ptr<std::mutex>& mutex, const std::shared_ptr<std::condition_variable>& cond) {
	this->mutexR = mutex;
	this->data_cond = cond;
}

void Reader::read() {
	std::getline(std::cin, inputStr);

	if (inputStr.size() >= maxLength || !IsStrOnlyNumbers(inputStr)) {
		throw ThreadException("Failed to read. Input string must contain integers and have a length of no more than 64 characters",
			ThreadException::who_t::READER);
	}
}

std::string Reader::parseStrToBuffer() {
	std::sort(inputStr.begin(), inputStr.end(), [](char const& c1, char const& c2) {
		return c1 > c2;
		});

	std::string newStr, kb = "KB";
	for (size_t i = 0; i < inputStr.size(); i++)
	{
		if (inputStr[i] % 2 == 0) {
			newStr += kb;
		}
		else {
			newStr += inputStr[i];
		}
	}
	return newStr;
}

void Reader::run(std::vector<std::string>& buffer, std::atomic_bool& isReadable) {
	while (std::cin.good()) {
		try {
			read();

			std::string curLine = parseStrToBuffer();
			std::unique_lock<std::mutex> lock(*mutexR);
			buffer.push_back(std::move(curLine));
			data_cond->notify_one();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
	isReadable = false;
}