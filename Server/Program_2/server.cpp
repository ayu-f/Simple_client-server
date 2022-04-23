#include"server.hpp"

void Server::run() {
    RC rc = connect();
    if (rc != RC::SUCCESS) {
        printError(rc);
        return;
    }

    rc = processMessege();
    printError(rc);
}


Server::RC Server::connect() {
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        return RC::ERR_SOCKET_CREATING;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(listener, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        return RC::ERR_BIND;
    }

    listen(listener, 1); // 1 - request queue size
    return RC::SUCCESS;
}

Server::RC Server::processMessege() {
    while (true)
    {
        sock = accept(listener, NULL, NULL);
        if (sock < 0)
        {
            return RC::ERR_ACCEPT;
        }

        while (true)
        {
            bytesRead = recv(sock, buf, 1024, 0);
            if (bytesRead <= 0) {
                printError(RC::ERR_READ);
                break;
            }

            RC rc = analyzeData(buf);
            if (rc != RC::SUCCESS) {
                printError(rc);
            }
        }
        close(sock);
    }
    return RC::SUCCESS;
}

Server::RC Server::analyzeData(const char* data) {
    std::string tmp(buf);
    if (tmp.size() <= 2)
        return RC::INCORRECT_DATA;

    int number;
    try {
        number = std::stoi(tmp);
    }
    catch (std::exception& e) {
        return RC::INCORRECT_DATA;
    }

    if (number % intMultiple != 0)
        return RC::INCORRECT_DATA;

    std::cout << "Data recieved: " << number << std::endl;
    return RC::SUCCESS;
}

void Server::printError(const RC& rc) {
    switch (rc)
    {
    case RC::ERR_ACCEPT:
        std::cout << "Error while serving the request" << std::endl;
        break;
    case RC::ERR_BIND:
        std::cout << "Socket binding error with address" << std::endl;
        break;
    case RC::ERR_READ:
        std::cout << "Data could not be read" << std::endl;
        break;
    case RC::ERR_SOCKET_CREATING:
        std::cout << "Error in socket creation" << std::endl;
        break;
    case RC::INCORRECT_DATA:
        std::cout << "Error: Incorrect data received" << std::endl;
        break;
    default:
        break;
    }
}