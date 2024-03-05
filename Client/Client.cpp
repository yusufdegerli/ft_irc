#include "Client.hpp"

Client::Client(int fd)
{
    this->usrUser = "";
    this->usrNick = "";
    this->socketNumber = fd;
    this->fd = fd;
    this->isLogged = false;
    this->inServer = false;
}

Client::Client()
{
    this->socketNumber = -1;
    this->realIp = -1;

    this->usrNick = "";
    this->usrUser = "";
    this->RealName = "";

    this->isLogged = false;
    this->inServer = false;
}

Client::Client(Client const &cpy){*this = cpy;}

void    Client::operator=(Client const &cpy)
{
    this->socketNumber = cpy.socketNumber;
    this->realIp = cpy.realIp;
    this->usrNick = cpy.usrNick;
    this->usrUser = cpy.usrUser;
    this->RealName = cpy.RealName;
    this->isLogged = cpy.isLogged;
    this->inServer = cpy.inServer;
}

void Client::setSocket(const int socket)
{
    this->socketNumber = socket;
}

void Client::setRealName(const std::string &RealName)
{
    this->RealName = RealName;
    std::cout << "user host: " << this->RealName << std::endl;
}

void Client::setUsrNick(const std::string &usrNick)
{
    this->usrNick = usrNick;
    std::cout << "Client " << this->socketNumber << " set nickname: " << this->usrNick <<std::endl;
    this->print("Welcome, " + this->getNick() + "\n");
}

/* void Client::setUsrName(const std::string &usrName)
{
    this->usrName = usrName;
    std::cout << "Client " << this->socketNumber << " set nickname: " << this->usrName <<std::endl;
    this->print("Real name: " + this->usrName + "\n");
} */

void Client::setUsername(const std::string &usrUser)
{
    this->usrUser = usrUser;
    std::cout << "user: " << this->usrUser << std::endl;
}

void Client::setRealIp(const std::string &realIp)
{
    this->realIp = realIp;
    std::cout << "user ip: " << this->realIp << std::endl;
}

Client::~Client(){}

void Client :: setLoggin(bool status)
{
    std::cout << "Client " << this->socketNumber << " logged in the system" << std::endl;
    this->isLogged = status;
}

int Client :: getFd()
{
    return this->fd;
}

void Client :: setFd(int fd)
{
    this->fd = fd;
}

int Client :: getSocket()
{
    return this->socketNumber;
}

bool Client :: getLoggedStatus()
{
    return this->isLogged;
}

void Client :: print(std::string str)
{
    send(this->socketNumber, str.c_str(), str.length(),  0);
}

void Client :: clientInfo(Client &receive, Client &client)
{
    receive.print(":" + client.getNick() + "!" + client.getUsername() + "@" + client.getRealIp() + " ");
}

std::string Client :: getNick() const
{
    return this->usrNick;
}

/* std::string Client :: getName()
{
    return this->usrName;
} */

std::string Client :: getUsername()
{
    return this->usrUser;
}

std::string Client :: getRealName()
{
    return this->RealName;
}

std::string &Client::getRealIp() {return this->realIp;}

bool Client::getinServer(){return this->inServer;}

void Client::setInServer(bool status){this->inServer = status;}

bool Client::ifHasInvitation(std::string chan)
{
    for (size_t m = 0; m < this->hasInvitationTo.size(); m++)
    {
        if (this->hasInvitationTo[m] == chan)
            return true;
    }
    return false;
}
void Client::setHasInvitationTo(std::string channel)
{
    this->hasInvitationTo.push_back(channel);
}

