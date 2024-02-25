#pragma once
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sstream>
#include <string>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <vector>
#include <poll.h>

#include "Client.hpp"
class Client;

class Server
{
    private:
        std::vector<struct pollfd>  fds;
        int sockfd;
        int port;
        std::string password;
        int acceptfd;

        sockaddr_in server_address;
        int serverfd;
        int optv;
        socklen_t adr_len;
        int acc_val;
    public:
        Server();
        Server(Server const &cpy);
        void operator=(const Server &val);
        Server(int port, std::string password);
        ~Server();

        void serverFunc();
        void setServerfd(int server_fd);
        void check_bind_status(int bind_val);
        void check_listen_status(int list_val);
        void check_accept_status(int accept_val);

    
};
//void serverFunc();
void pieceByPiece(char *buff, std::vector<std::string> &bufferRaw);