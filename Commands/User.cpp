#include "../Server/Server.hpp"

void Server :: USER(Client &client)
{
    if (client.getinServer() == false)
    {
        client.print("Log into the system first. Use PASS command\n");
        return ;
    }
    if (!client.getUsername().empty() && !client.getRealName().empty() && client.getLoggedStatus())
    {
        client.print("Real name is already set\n");
        return ;
    }

    if (this->commands.size() < 5)
    {
        client.print(":" + client.getRealIp() + " 462 " + client.getNick() + " USER : Not enough parameters\r\n");
        return ; 
    }

    if (this->commands.size() == 5 && this->commands[2].compare("0") == 0)
    {
        time_t rawtime;
        struct tm *timeinfo;

        char buffer[80];
        std::time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
        client.setLoggin(true);
        //LINE 1
        client.print(":" + client.getRealIp() + " 001 " + client.getNick() + " : Welcome to the Internet Relay Network " \
        + client.getNick() + "!" + this->commands[1] + client.getUsername() + "@" + client.getRealIp() + "\r\n");

        //LINE 2
        client.print(":" + client.getRealIp() + " 002 " + client.getNick() + " : Your host is " + client.getRealIp() + ", running version v1.0\r\n");

        //LINE 3
        client.print(":" + client.getRealIp() + " 003 " + client.getNick() + " This server was created " + std::string(buffer) + "\r\n");

        //LINE 4 UNKNOWN will gonna change
        client.print(":" + client.getRealIp() + " 251 " + client.getNick() + " There are " + std::to_string(this->clients.size()) + " users and 0 services on 1 server\r\n");
        client.setRealName(this->commands[4]);
        client.setUsername(this->commands[1]);
        return ;
    }
    else // maybe something like wrong usage is better
    {
        client.print(":" + this->getServerIP() + " 462 " + client.getNick() + "USER : You may not reregister\r\n");
        return ; 
    }
    
}