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

#include "../Client/Client.hpp"
#include "../Command.hpp"
class Command;
class Client;

class Server
{
    private:
        std::vector<struct pollfd >  fds;
        int sockfd;
        int port;
        std::string password;
        int acceptfd;

        sockaddr_in server_address;
        int serverfd;
        int optv;
        socklen_t adr_len;
        int acc_val;

        std::vector<Client> clients;
        std::vector<std::string> commands;
    public:
        Server();
        Server(Server const &cpy);
        void operator=(const Server &val);
        Server(int port, std::string password);
        ~Server();

        void serverFunc();
        void setServerfd(int server_fd);
        void checkBindStatus(int bind_val);
        void checkListenStatus(int list_val);
        void checkAcceptStatus(int accept_val);
        void userAccept();
        void checkPollStatus(int poll_status);
        int getAccVal();


        void parseMessage(char *buffer);
        void executeCommands(int fd);
        void PASS(Client &client);
        void NICK(Client &client);
        void USER(Client &client);
        int checkActivation(Client &client);
        void start();
        int checkRecvStatus(int recv_val, int i);
};
void pieceByPiece(char *buff, std::vector<std::string> &bufferRaw);