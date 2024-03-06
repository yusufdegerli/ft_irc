#include "../Server/Server.hpp"

void Server::PART(Client &client)
{
    std::string channels = this->commands[1];
    std::string reason = "";

    if(this->checkActivation(client) == -1)
        return ;
    if (this->commands.size() < 2)
    {
        client.print(":" + this->getServerIP() + " 461 " + client.getNick() + " PART :Not enough parameters" + "\r\n");
        return ;
    }
    if (this->commands.size() == 3)
        reason = this->commands[2];
    std::vector<std::string> channel_list;
    channel_list = create_list(channels);

    for (size_t j = 3; j < this->commands.size(); j++)
        reason += " " + this->commands[j];
    for (size_t k = 0; k < channel_list.size(); k++)
    {
        if (this->findChannel(channel_list[k]))
        {
            Channel &chan = this->channels[returnChannelIndex(channel_list[k])];
            size_t i = 0;
            size_t before_erase = chan.getMembers().size();
            for (i = 0; i < chan.getMembers().size(); i++)
            { 
                if (client.getNick() == chan.getMembers()[i].getNick())
                {
                    for (size_t m = 0; m < chan.getMembers().size(); m++)
                        chan.getMembers()[m].print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " PART " + chan.getName() + " "+ reason + "\r\n");
                    chan.getMembers().erase(chan.getMembers().begin() + i);
                    if (chan.getMembers().empty())
                        this->channels.erase(this->channels.begin() + this->returnChannelIndex(chan.getName()));
                    break ;
                }
            }
            if (i >= before_erase)
            {
                client.print(":" + this->getServerIP() + " 442 " + client.getNick() + ": No such nick/channel\r\n");
                return ;
            }
        }
        else
        {
            client.print(":" + this->getServerIP() + " 403 " + client.getNick() + ": No such nick/channel\r\n");
            client.print(client.getNick() + " " + channel_list[k] + " :No such channel" + "\r\n");
        }
    }

}
