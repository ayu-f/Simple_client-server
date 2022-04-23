#include"Sender.hpp"

Sender::Sender(const std::shared_ptr<std::mutex>& mutex, const std::shared_ptr<std::condition_variable>& cond) {
	this->mutexW = mutex;
	this->data_cond = cond;
}

int Sender::calcSum(std::string& str) {
	int sum = 0;
	for (auto& c : str) {
		if (isdigit(c)) {
			sum += c - 48;
		}
	}
	return sum;
}

bool Sender::connect_until() { // try to connect before 30 seconds have passed
	auto start = std::chrono::high_resolution_clock::now();
	bool isConnect = false;
	while (!(isConnect = client.connectToServer())) {
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> dur = end - start;
		if (dur.count() >= timeToWait)
			break;
	}
	return isConnect;
}

void Sender::run(std::vector<std::string>& buffer, std::atomic_bool& isReadable) {
	try {
		if (!client.connectToServer()) {
			throw ThreadException("Server connection error.", ThreadException::who_t::SENDER);
		}
		while (isReadable) {
			std::unique_lock<std::mutex> lock(*mutexW);
			data_cond->wait(lock, [&buffer]() {
				return buffer.size() != 0; });

			std::vector<std::string> lines(std::move(buffer));
			lock.unlock();

			if (!isReadable)
				return;
			
			for (auto&& s : lines) {
				std::cout << "Changed data: " << s << std::endl;
				std::string sum = std::to_string(calcSum(s));
				if (!client.sendToServer(sum)) {
					std::cout << "Connection lost, attempt to reconnect. Waiting time 30s" << std::endl;
					if (connect_until()) {
						std::cout << "Success!" << std::endl;
						client.sendToServer(sum);
					}
					else
						throw ThreadException("Unable to reconnect", ThreadException::who_t::SENDER);

				}
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}