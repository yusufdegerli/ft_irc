#include "../Server/Server.hpp"

void Server :: WHO(Client &client)
{
    size_t i = 0;
    if(this->commands[1][0] == '#' && this->findChannel(this->commands[1]))
    {
        for (size_t j = 0; j < this->channels[returnChannelIndex(this->commands[1])].getMembers().size(); j++)
        {
            client.print("Nick: " + this->clients[j].getNick() + "\n");
        }
        client.print(":" + client.getRealIp() + " 315 " +  this->commands[1] + ": End of WHO list\r\n");
        return ;
    }
    else
    {
        for (; i < this->channels.size(); i++)
        {
            for (size_t m = 0; m < this->channels[i].getMembers().size(); m++)
            {
                if(this->commands[1].compare(this->channels[i].getMembers()[i].getNick()) == 0)
                {
                    client.print("Nick: " + this->channels[i].getMembers()[i].getNick() + "\n");
                    client.print("Ip: " + this->channels[i].getMembers()[i].getRealIp() + "\n");
                    client.print("Hostname: " + this->channels[i].getMembers()[i].getHostname() + "\n");
                    client.print("Username: " + this->channels[i].getMembers()[i].getUsername() + "\n");
                    //client.print("Name: " + this->channels[i].getMembers()[i].getName() + "\n");
                }
                break ;
            }
        }
    }
    client.print(":" + client.getRealIp() + " 315 " + client.getNick() + ": End of WHO list\r\n");
}
