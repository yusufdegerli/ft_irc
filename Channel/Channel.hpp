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
        std::vector<Client> members;
        std::string key;
        bool key_required;
    public:
        Channel();
        Channel(std::string const &name);
        Channel(Channel const &New);
        void    operator=(Channel const &New);
        ~Channel();
        
        void    addToMembers(Client const &New);

        std::string getName(void);
        std::vector<Client> getMembers(void);
        std::string getKey(void);
        bool getKeyRequired();
};
