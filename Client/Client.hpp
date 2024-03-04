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
    private:
        int socketNumber;
        std::string hostName;
        int information;
        std::string uId;

        std::string usrPass;
        std::string usrNick;
        std::string usrIp;
        // std::string usrName;
        std::string usrSurname;
        std::string usrUser;
        std::string realIp;

        int fd;
        bool isLogged;
        bool isActive;
    public:
        Client();
        void operator=(Client const &cpy);
        Client(Client const &cpy);
        //Client(int hostName, std::string uId);
        
        void setSocket(const int socket);
        void setHostname(const std::string &hostname);
        void setuId(const std::string &uId);
        void setUsrPass(const std::string &usrPass);
        void setUsrNick(const std::string &usrNick);
        void setUsrIp(const std::string &usrIp);
        // void setUsrName(const std::string &usrName);
        void setUsrSurname(const std::string &usrSurname);
        void setUsername(const std::string &usrUser);
        void setRealIp(const std::string &realIp);
        void setInformation(const int &information);
        void setFd(int fd);
        void setLoggin();
        
        std::string &getRealIp();
        int getInformation()const;
        
        //Client(std::string usrPass, std::string usrNick, std::string usrUser, std::string usrIp, std::string usrName, std::string usrSurname);
        ~Client();
        Client(int fd);
        bool getLoggedStatus();
        void print(std::string str);
        std::string clientInfo(Client &client);
        
        int getFd();
        int getSocket();
        std::string getNick() const;
        // std::string getName();
        std::string getUsername();
        std::string getHostname();
};