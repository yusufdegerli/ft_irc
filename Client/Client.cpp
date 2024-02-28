#include "Client.hpp"

Client::Client(int fd)
{
    this->usrName = "";
    this->usrNick = "";
    this->fd = fd;
    this->isActive = false;
    this->isLogged = false;
    std::cout << "fd " << this->fd << std::endl;
}

Client::Client()
{
    this->socketNumber = -1;
    this->uId = -1;
    this->usrIp = -1;
    this->realIp = -1;
    this->information = 1;

    this->usrName = "";
    this->usrNick = "";
    this->usrPass = "";
    this->usrSurname = "";
    this->usrUser = "";
    this->hostName = "";
}

Client::Client(Client const &cpy) : information(cpy.information)
{
    this->socketNumber = cpy.socketNumber;
    this->uId = cpy.uId;
    this->usrIp = cpy.usrIp;
    this->realIp = cpy.realIp;
    this->usrName = cpy.usrName;
    this->usrNick = cpy.usrNick;
    this->usrPass = cpy.usrPass;
    this->usrSurname = cpy.usrSurname;
    this->usrUser = cpy.usrUser;
    this->hostName = cpy.hostName;
}

void    Client::operator=(Client const &cpy)
{
    this->socketNumber = cpy.socketNumber;
    this->uId = cpy.uId;
    this->usrIp = cpy.usrIp;
    this->realIp = cpy.realIp;
    this->usrName = cpy.usrName;
    this->usrNick = cpy.usrNick;
    this->usrPass = cpy.usrPass;
    this->usrSurname = cpy.usrSurname;
    this->usrUser = cpy.usrUser;
    this->hostName = cpy.hostName;
}

/* Client::Client(int hostName, std::string uId)
{
    this->hostName = hostName;
    this->uId = uId;
    this->usrName = "";
} */

/* Client::Client(std::string usrPass, std::string usrNick, std::string usrUser, std::string usrIp, std::string usrName, std::string usrSurname)
{
    this->usrPass = usrPass;
    this->usrNick = usrNick;
    this->usrUser = usrUser;
    this->usrIp = usrIp;
    this->usrName = usrName;
    this->usrSurname = usrSurname;
    std::cout << "KULLANICI BİLGİLERİ\n";
    std::cout << "user password: " << this->usrPass << std::endl;
    std::cout << "user nick: " << this->usrNick << std::endl;
    std::cout << "user ip: " << this->usrIp << std::endl;
    std::cout << "user name: " << this->usrName << std::endl;
    std::cout << "user: " << this->usrUser << std::endl;
    std::cout << "user surname: " << this->usrSurname << std::endl;
} */

void Client::setSocket(const int socket)
{
    this->socketNumber = socket;
}

void Client::setHostname(const std::string &hostname)
{
    this->hostName = hostname;
    std::cout << "user host: " << this->hostName << std::endl;
}

void Client::setuId(const std::string &uId)
{
    this->uId = uId;
}

void Client::setUsrPass(const std::string &usrPass)
{
    this->usrPass = usrPass;
    std::cout << "user password: " << this->usrPass << std::endl;
}

void Client::setUsrNick(const std::string &usrNick)
{
    this->usrNick = usrNick;
    std::cout << "Client " << this->socketNumber << " set nickname: " << this->usrNick <<std::endl;
    this->print("Welcome, " + this->getNick() + "\n");
}

void Client::setUsrIp(const std::string &usrIp)
{
    this->usrIp = usrIp;
}

void Client::setUsrName(const std::string &usrName)
{
    this->usrName = usrName;
    std::cout << "Client " << this->socketNumber << " set nickname: " << this->usrName <<std::endl;
    this->print("Real name: " + this->usrName + "\n");
}

void Client::setUsrSurname(const std::string &usrSurname)
{
    this->usrSurname = usrSurname;
    std::cout << "user surname: " << this->usrSurname << std::endl;
}

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

void Client::setInformation(const int &information)
{
    this->information = information;
}

int Client::getInformation()const{return this->information;}

Client::~Client(){}

void Client :: setLoggin()
{
    this->isLogged = true;
    std::cout << "Client " << this->socketNumber << " logged in the system" << std::endl;
    this->print("You are in the system\n");
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
    // std::cout << str << std::endl;
}

std::string Client :: getNick()
{
    return this->usrNick;
}

std::string Client :: getName()
{
    return this->usrName;
}

std::string Client :: getUsername()
{
    return this->usrUser;
}

std::string Client :: getHostname()
{
    return this->hostName;
}