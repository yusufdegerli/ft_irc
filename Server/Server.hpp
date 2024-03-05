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
#include "../Channel/Channel.hpp" 
class Client;
class Channel;

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
        std::string serverIP;

        std::vector<Client> clients;
        std::vector<Channel> channels;
        std::vector<std::string> commands;
    public:
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
        void MODE(Client &client);

        void JOIN(Client &client);
        void INVITE(Client &client);
        void PART(Client &client);
        void TOPIC(Client &client);

        void QUIT(Client &client);
        void WHO(Client &client);
        void PRIVMSG(Client &client);
        void KICK(Client &client);
        void LIST(Client &client);
        

        int checkActivation(Client &client);
        void start();
        int checkRecvStatus(int recv_val, int i);

        bool findChannel(std::string channel);
        size_t returnClientIndex(std::string clientNick, Channel &channel);
        size_t returnChannelIndex(std::string channel);
        void addToChannel(Channel &chan, Client &client);
        
        int getClient(std::string nick);

        std::string getServerIP(void);
};

std::vector<std::string> create_list(std::string str);