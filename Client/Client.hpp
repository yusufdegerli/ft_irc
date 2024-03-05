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

#include "../Server/Server.hpp"
class Server;

class Client
{
    protected:
        int socketNumber;
        std::string RealName;

        std::string usrNick;
        std::string usrUser;
        std::string realIp;

        int fd;
        bool isLogged;
        bool inServer;
        std::vector<std::string> hasInvitationTo;
    public:
        Client();
        void operator=(Client const &cpy);
        Client(Client const &cpy);
        
        void setSocket(const int socket);
        void setRealName(const std::string &RealName);
        void setUsrNick(const std::string &usrNick);
        void setUsername(const std::string &usrUser);
        void setRealIp(const std::string &realIp);
        void setFd(int fd);
        void setLoggin(bool status);
        
        std::string &getRealIp();
        
        ~Client();
        Client(int fd);
        bool getLoggedStatus();
        void print(std::string str);
        void clientInfo(Client &receive, Client &client);
        
        int getFd();
        int getSocket();
        std::string getNick() const;
        std::string getUsername();
        std::string getRealName();
        bool getinServer();
        void setInServer(bool status);
        bool ifHasInvitation(std::string chan);
        void setHasInvitationTo(std::string channel);

};