#include "../Server/Server.hpp"

void Server :: USER(Client &client)
{
    if (client.getName() != "")
    {
        client.print("Real name is already set\n");
        return ;
    }
    if (client.getLoggedStatus() == 0)
    {
        client.print("Log into the system first. Use PASS command\n");
        return ;
    }
    
    if (client.getNick() == "")
    {
        client.print("Set nickname first. Use NICK command\n");
        return ;
    }

    if (this->commands.size() == 5 && this->commands[2].compare("0") == 0 && this->commands[3].compare("*") == 0)
    {
        time_t rawtime;
        struct tm *timeinfo;

        char buffer[80];
        std::time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
        //LINE 1
        client.print(":"); client.print(client.getRealIp()); client.print(" 001 "); client.print(client.getNick());
        client.print(" : Welcome to the Internet Relay Network ");client.print(client.getNick());client.print("!");client.print(this->commands[1]);
        client.print(client.getUsername());client.print("@");client.print(client.getRealIp());client.print("\n");

        //LINE 2
        client.print(":"); client.print(client.getRealIp()); client.print(" 002 "); client.print(client.getNick());
        client.print(" : Your host is "); client.print(client.getRealIp());client.print(", running version v1.0\n");

        //LINE 3
        client.print(":"); client.print(client.getRealIp()); client.print(" 003 "); client.print(client.getNick());
        client.print(" This server was created ");client.print(std::string(buffer));

        //LINE 4 UNKNOWN will gonna change
        client.print(":"); client.print(client.getRealIp()); client.print(" 251 "); client.print(client.getNick());
        client.print(" There are ");client.print("UNKOWN!"); client.print(" users and 0 services on 1 server\n");
        return ;
    }
    else
    {
        client.print("Wrong arguments\n");
        return ; 
    }

    client.setUsername(this->commands[1]);
    client.setHostname(this->commands[3]);
}