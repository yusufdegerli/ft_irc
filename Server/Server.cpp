#include "Server.hpp"

Server::Server()
{
    this->password = "";
    this->serverIP = "";
    this->optv = 1;
}

Server::Server(Server const &New){*this = New;}
void    Server::operator=(Server const &New)
{
    this->acc_val = New.acc_val;
    this->acceptfd = New.acceptfd;
    this->adr_len = New.adr_len;
    this->channels = New.channels;
    this->clients = New.clients;
    this->commands = New.commands;
    this->fds = New.fds;
    this->optv = New.optv;
    this->password = New.password;
    this->port = New.port;
    this->server_address = New.server_address;
    this->serverfd = New.serverfd;
    this->serverIP = New.serverIP;
    this->sockfd = New.sockfd;
}

Server::Server(int port, std::string password)
{
    this->port = port;
    this->password = password;
    this->optv = 1;

    this->server_address.sin_family = AF_INET;
    this->server_address.sin_port = htons(this->port);
    this->server_address.sin_addr.s_addr = INADDR_ANY;
    this->serverIP = inet_ntoa(this->server_address.sin_addr);
    this->adr_len = sizeof(this->server_address);
}

void Server :: userAccept()
{
    struct pollfd connect;

    if (this->fds[0].revents & POLLIN)
    {
        checkAcceptStatus(accept(this->serverfd, (sockaddr *)&this->server_address, &this->adr_len));
        
        Client client(this->acc_val);
        this->clients.push_back(client);
        this->clients[this->acc_val - 4].setFd(this->acc_val);

        this->clients[this->acc_val - 4].setSocket(this->acc_val);
        unsigned long clientAddr = ntohl(this->server_address.sin_addr.s_addr);
        std::string clientIP = std::to_string((clientAddr >> 24) & 0xFF) + "." + std::to_string((clientAddr >> 16) & 0xFF) + "." + std::to_string((clientAddr >> 8) & 0xFF) + "." + std::to_string(clientAddr & 0xFF);
        this->clients[this->acc_val - 4].setRealIp(clientIP);

        std::cout << "Client " << this->acc_val << " connected successfully" << std::endl;
        this->fds.push_back(connect);
        this->fds[this->acc_val - 3].fd = this->acc_val;
        this->fds[this->acc_val - 3].events = POLLIN;
    }
}

void Server :: start()
{
    this->setServerfd(socket(AF_INET, SOCK_STREAM, 0));
    setsockopt(this->serverfd, SOL_SOCKET, SO_REUSEADDR, &this->optv, sizeof(this->optv));
    
    checkBindStatus(bind(this->serverfd, (const sockaddr *)&this->server_address, this->adr_len)); // istenilen soketi, verilen adrese bağlıyor. BU kadar!
    checkListenStatus(listen(this->serverfd, 5));//Gelen bağlantıları, bekletir. İkinci parametre kaç tane bağlantının beklemesi gerektiğini söyler.
    
    struct pollfd server;
	this->fds.push_back(server);
    this->fds[0].fd = this->serverfd;
    this->fds[0].events = POLLIN;


    std::cout << "Server is listening..." << std::endl;
}

void Server :: serverFunc()
{
    std::vector<std::string> bufferRaw;

    this->start();

    while(1)
    {
        checkPollStatus(poll(&(this->fds[0]), this->fds.size(), -1));// Süresiz bekleyin
        userAccept();
        for (size_t i = 1; i < this->fds.size(); i++)
        {
            if (this->fds[i].fd != -1 && this->fds[i].revents & POLLIN) {
                char buff[1024] = {0}; // her recv fonksiyonu çalıştığında saçma sapan, ascii dışında karakterler geliyor. Böyle yaparak bunu önlüyorum.
                if (checkRecvStatus(recv(this->fds[i].fd, buff, sizeof(buff), 0), i) == 1)
                {
                    std::cout << "client message: " << buff << std::endl;
                    parseMessage(buff);
                    executeCommands(i);
                }
            }
        }

    }
    close(this->acc_val);
    close(this->serverfd);
}

bool Server :: findChannel(std::string channel)
{
    for (size_t i = 0; i < this->channels.size(); i++)
    {
        if (this->channels[i].getName() == channel)
            return true;
    }

    return false;
}

size_t Server::returnClientIndex(std::string clientNick, Channel &channel)
{
    size_t i = 0;
    for(; i < channel.getMembers().size(); i++)
    {
        if(channel.getMembers()[i].getNick() == clientNick)
            return i;
    }
    return i;
}

size_t Server :: returnChannelIndex(std::string channel)
{
    size_t i = 0;

    for (; i < this->channels.size(); i++)
    {
        if (this->channels[i].getName() == channel)
            return i;
    }

    return i;
}

void Server :: addToChannel(Channel &chan, Client &client)
{
    std::string symbol;
    std::string prefix;

    if (chan.checkMembers(client) == false)
    {
        chan.addToMembers(client);
        for (size_t m = 0; m < chan.getMembers().size(); m++)
        {
            client.clientInfo(chan.getMembers()[m], client);
            chan.getMembers()[m].print("JOIN " + chan.getName() + "\r\n");
        }
        if (chan.getTopic() != "")
        {
            client.clientInfo(client, client);
            client.print(client.getNick() + " " + chan.getName() + " :" + chan.getTopic());
        }
        client.clientInfo(client, client);
        client.print(client.getNick() + " = " + chan.getName()  + " :");
        chan.checkOperators(client) ? prefix = "@" : prefix = "v";
        client.print(prefix + client.getNick());
        for (size_t m = 0; m < chan.getMembers().size() - 1; m++)
        {
            client.print(" ");
            chan.checkOperators(chan.getMembers()[m]) ? prefix = "@" : prefix = "v";
            client.print(prefix + chan.getMembers()[m].getNick());
        }
        client.print("\r\n");
        client.clientInfo(client, client);
        client.print(client.getNick() + " " + chan.getName() + " :End of /NAMES list\r\n");
        for (size_t m = 0; m < chan.getMembers().size() - 1; m++)
        {
            client.clientInfo(client, chan.getMembers()[m]);
            client.print("JOIN " + chan.getName() + "\r\n");
        }
    }
    else
        client.print("You are already in the channel " + chan.getName() + "\r\n");
}

Server::~Server(){}

std::string Server :: getServerIP(void)
{
    return this->serverIP;
}

