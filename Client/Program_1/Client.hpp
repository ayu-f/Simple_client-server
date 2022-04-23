#ifndef _IF_CLIENT_INCLUDE
#define _IF_CLIENT_INCLUDE
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<iostream>

#define PORT 1234

// class for connecting to the server
class Client {
private:
    int server_fd, sock;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    bool isSocketActive = false;
public:
    bool connectToServer() {
        if (isSocketActive){
            close(sock);
            shutdown(sock, SHUT_WR);
            isSocketActive = false;
        }
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            return false;
        }
        else
            isSocketActive = true;
        
        address.sin_family = AF_INET;
        address.sin_port = htons(PORT);
        address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

        if (connect(sock, (struct sockaddr*)&address, sizeof(address)) < 0)
        {
            return false;
        }

        return true;
    }

    bool sendToServer(std::string const& str) {
        char const* msg = str.c_str();
        int a;
        if ((a = send(sock, msg, sizeof(msg), MSG_NOSIGNAL)) < 0) {
            return false;
        }

        return true;
    }

    ~Client() {
        close(sock);
    }
};

#endif // _IF_CLIENT_INCLUDE