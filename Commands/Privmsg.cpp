#include "../Server/Server.hpp"

void Server :: PRIVMSG(Client &client)
{
    //mesajdan önce ':' olmalı
    size_t i = 0;
    std::string message = "";
    for (size_t j = 2; j < this->commands.size(); j++)
    {
        message += this->commands[j];
        message += " ";
    }
    if (this->commands.size() == 1)
    {
        client.print(":" + client.getRealIp() + " 411 " + client.getNick() + ": No recipient given PRIVMSG\n");
        return ;
    }
    else if(this->commands.size() == 2)
    {
        client.print(":" + client.getRealIp() + " 412 " + client.getNick() + ": No recipient given PRIVMSG\n");
        return ;
    }
    for (; i < this->clients.size(); i++)
    {
        if(this->commands[1].compare(this->clients[i].getNick()) == 0)
        {
            clients[i].print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " PRIVMSG " + clients[i].getNick() + " :" + message + "\r\n");
            client.print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " PRIVMSG " + clients[i].getNick() + " :" + message + "\r\n");
            return ;
        }
        else if (this->commands[1].compare(this->channels[i].getName()) == 0)
        {
            for (size_t m = 0; m < this->channels[i].getMembers().size(); m++)
                this->channels[i].getMembers()[m].print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " PRIVMSG " + this->channels[i].getName() + " :"+ message + "\r\n");
            return ;
        }
    }
    if(i == clients.size())
    {
        client.print(":" + client.getRealIp() + " 401 " + client.getNick() + ": No such nick/channel\n");
        return ;
    }
}