#pragma once
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#define PORT 1234


class Server {
private:
    enum class RC {
        SUCCESS,
        ERR_BIND,
        ERR_SOCKET_CREATING,
        ERR_ACCEPT,
        ERR_READ,
        INCORRECT_DATA
    };

    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytesRead;
    const int intMultiple = 32;

    // print error if occurred
    void printError(const RC& rc);

    // connect to client
    RC connect();

    // get messages
    RC processMessege();

    // follow requirements
    RC analyzeData(const char* data);
public:
    void run();
};