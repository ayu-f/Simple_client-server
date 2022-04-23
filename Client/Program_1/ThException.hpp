#ifndef _IF_EXCEPTION_TH_INCLUDE
#define _IF_EXCEPTION_TH_INCLUDE
#include <iostream>


class ThreadException : public std::exception {
public:
	enum class who_t {
		READER,
		SENDER
	};

	ThreadException(std::string&& whatStr, who_t who) noexcept : whatStr(std::move(whatStr)) { 
		this->who = who; 
		buildMessege();
	}
	ThreadException(std::string const& whatStr, who_t who) noexcept : whatStr(whatStr) {
		this->who = who; 
		buildMessege();
	}
	~ThreadException() noexcept = default;

	const char* what() const noexcept override {
		return whatStr.c_str();
	}
private:
	void buildMessege() {
		std::string str;
		whatStr.append(" From: ");
		whatStr.append(who == who_t::READER ? "Reader" : "Writer");
	}

	std::string whatStr;
	who_t who;
};

#endif // _IF_EXCEPTION_TH_INCLUDE