#include "../Server/Server.hpp"

void Server::PART(Client &client)
{
    std::string channels = this->commands[1];
    std::string reason = this->commands[2];

    if (channels.empty())
    {
        client.print(client.getNick() + " PART :Not enough parameters" + "\r\n"); // 461
        return ;
    }
    std::vector<std::string> channel_list;
    channel_list = create_list(channels);

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
                        chan.getMembers()[m].print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " PART " + chan.getName() + "\r\n");
                    chan.getMembers().erase(chan.getMembers().begin() + i);
                    break ;
                }
            }
            if (i >= before_erase)
            {
                client.print(client.getNick() + " " + chan.getName() + " :You're not on that channel" + "\r\n"); // 442
                return ;
            }
        }
        else
        {
            client.print(client.getNick() + " " + channel_list[k] + " :No such channel" + "\r\n"); // 403
        }
    }

}