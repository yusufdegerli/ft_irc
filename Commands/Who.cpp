#include "../Server/Server.hpp"

void Server :: WHO(Client &client)
{
    size_t i = 0;
    size_t j = 0;
    if(this->checkActivation(client) == -1)
        return ;
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
    Channel &chan = this->channels[returnChannelIndex(this->commands[1])];
        for (; i < this->channels.size(); i++)
        {
            for (size_t m = 0; m < this->channels[i].getMembers().size(); m++)
            {
                if(this->commands[1].compare(this->channels[i].getMembers()[m].getNick()) == 0)
                {
                    client.print("Nick: " + this->channels[i].getMembers()[m].getNick() + "\n");
                    client.print("Ip: " + this->channels[i].getMembers()[m].getRealIp() + "\n");
                    client.print("RealName: " + this->channels[i].getMembers()[m].getRealName() + "\n");
                    client.print("Username: " + this->channels[i].getMembers()[m].getUsername() + "\n");
                    for (; j < chan.getOperators().size(); j++)
                    {
                        if(this->channels[i].getMembers()[m].getNick().compare(chan.getOperators()[j].getNick()) == 0)
                        {
                            client.print("Operator: Yes\n");
                            break ;
                        }
                    }
                    if(j == chan.getOperators().size())
                        client.print("Operator: No\n");
                }
                else
                {
                    client.print("There's no member that you wrote\n");
                    return ;
                }
                break ;
            }
        }
    }
    client.print(":" + client.getRealIp() + " 315 " + client.getNick() + ": End of WHO list\r\n");
}
