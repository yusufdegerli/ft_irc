#include "Client.hpp"

Client::Client(int hostName, std::string uId)
{
    this->hostName = hostName;
    this->uId = uId;
}

Client::Client(std::string usrPass, std::string usrNick, std::string usrUser, std::string usrIp, std::string usrName, std::string usrSurname)
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
}

Client::~Client(){}