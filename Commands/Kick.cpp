#include "../Server/Server.hpp"

void Server :: KICK(Client &client)
{
    if(this->checkActivation(client) == -1)
        return ;
    std::string comment = "";
    for (size_t j = 0; j < this->commands.size(); j++)
    {
        comment += this->commands[j];
        comment += " ";
    }
    Channel &chan = this->channels[returnChannelIndex(this->commands[1])];
    if(this->commands.size() < 2)
    {
        client.print(":" + this->getServerIP() + " 461 " + client.getNick() + "KICK : Not enough parameters\r\n");
        return ;
    }
    else if(this->findChannel(this->commands[1]) == false)
    {
        client.print(":" + this->getServerIP() + " 403 " + client.getNick() + "KICK: No such channel\r\n");
        return ;
    }
    else if(this->findChannel(this->commands[1]) == true && chan.checkMembers(client) == false)
    {
        client.print(":" + this->getServerIP() + " 442 " + client.getNick() + "KICK: You are not on that channel\r\n");
        return;
    }
    else if(this->findChannel(this->commands[1]) == true && chan.checkMembers(chan\
    .getMembers()[returnClientIndex(this->commands[2], chan)]) == false)
    {
        client.print(":" + this->getServerIP() + " 441 " + client.getNick() + "KICK: They aren't on that channel\r\n");
        return ;
    }
    else
    {
        for (size_t i = 0; client.getNick() != chan.getMembers()[i].getNick(); i++)
            { 
                for (size_t m = 0; m < chan.getMembers().size(); m++)
                    chan.getMembers()[m].print("KICK " + chan.getName() + " " + client.getNick() + comment);
                chan.getMembers().erase(chan.getMembers().begin() + i);
                break ;
            }
    }
}