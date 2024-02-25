#pragma once
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <vector>
#include <poll.h>

#include "Server.hpp"
class Server;

class Client
{
    private:
        int socketNumber;
        int hostName;
        std::string uId;

        std::string usrPass;
        std::string usrNick;
        std::string usrIp;
        std::string usrName;
        std::string usrSurname;
        std::string usrUser;
        std::string realIp;
    public:
        Client();
        void operator=(Client const &cpy);
        Client(Client const &cpy);
        Client(int hostName, std::string uId);
        void setRealIp(const std::string &realIp);
        void setSocket(const int socket);
        std::string &getRealIp()const;
        Client(std::string usrPass, std::string usrNick, std::string usrUser, std::string usrIp, std::string usrName, std::string usrSurname);
        ~Client();
};