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

#include "../Client/Client.hpp"
class Client;

class Channel{
    private:
        std::string topic;
        std::string name;
        std::vector<Client> Operators;
        std::vector<Client> members;
        std::string key;
        bool key_required;
        bool invite_only;

    public:
        Channel();
        // Channel(std::string const &name);
        Channel(std::string name);
        Channel(std::string name, std::string key);
        Channel(Channel const &New);
        void    operator=(Channel const &New);
        ~Channel();
        
        void    addToOperators(Client const &New);
        void    addToMembers(Client const &New);

        std::string getName(void);
        std::vector<Client> getMembers(void);
        std::vector<Client> getOperators(void);
        std::string getKey(void);
        bool getKeyRequired();
        bool getInviteOnly();
        bool checkMembers(Client const &New);
        void printMembers();
        //void writeMembersByName(std::vector<Client> members);
};
