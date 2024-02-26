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


class Channel{
    private:
        std::string topic;
    public:
        Channel();
        Channel(Channel const &New);
        void    operator=(Channel const &New);
        ~Channel();

};
