#include "../Server/Server.hpp"

std::vector<std::string> create_list(std::string str)
{
    std::vector<std::string> new_list;

    size_t end = str.find(',');
    size_t start = 0;

    while (end != std::string::npos)
    {
        new_list.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(',', start);
    }
    if (start != str.length())
        new_list.push_back(str.substr(start));
    else
        new_list.push_back("");
    std::cout << new_list.back() << std::endl;
    return(new_list);
}

void Server :: JOIN(Client &client)
{
    std::string channels = this->commands[1];
    std::vector<std::string> key_list;
    std::string keys;

    if(this->checkActivation(client) == -1)
        return ;

    if (this->commands.size() < 2)
    {
        client.print(":" + client.getRealIp() + " 461 " + client.getNick() + "JOIN : Not enough parameters\r\n");
        return ;
    }
    if (this->commands.size() < 3)
    {
        keys = "";
        key_list.push_back("");
    }
    else
    {
        keys = this->commands[2];
        key_list = create_list(keys);
    }
    if (channels == "0" && this->commands.size() == 2)
    {
        for (size_t m = 0; m < this->channels.size(); m++)
        {
            this->commands.clear();
            this->commands.push_back("PART");
            this->commands.push_back(this->channels[m].getName());
            this->PART(client);
        }
        return ;
    }
    std::vector<std::string> channel_list;
    channel_list = create_list(channels);

    for (size_t i = 0; i < channel_list.size(); i++)
    {
        if(channel_list[i][0] != '#')
        {
            client.print("JOIN: There is no # in the first character.\n");
            channel_list.clear();
            key_list.clear();
            return ;
        }
        if (this->findChannel(channel_list[i]))
        {
            Channel &chan = this->channels[returnChannelIndex(channel_list[i])];
            if (chan.getKeyRequired() && !chan.getInviteOnly())
            {
                if (!keys.empty())
                {
                    if (key_list[i] == chan.getKey())
                        this->addToChannel(chan, client);
                }
                else
                {
                    client.print(":" + this->getServerIP() + " 475" + client.getNick() + " " + chan.getName() + " :Cannot join channel (+k)" + "\r\n");
                    channel_list.clear();
                    key_list.clear();
                    return ;
                }
            }
            else
            {
                if (chan.getInviteOnly() && !client.ifHasInvitation(chan.getName()))
                {
                    client.print(":" + this->getServerIP() + " 473" + client.getNick() + " " + chan.getName() + " :Cannot join channel (+i)\n");
                    channel_list.clear();
                    key_list.clear();
                    return ;
                }
                else
                    this->addToChannel(chan, client);
            }
        }
        else
        {
            if (key_list[i] != "")
            {
                Channel chan(channel_list[i], key_list[i]);
                this->channels.push_back(chan);

                std::cout << client.getNick() << " created channel: " << channel_list[i] << " that requires key" << std::endl;
            }
            else
            {
                Channel chan(channel_list[i]);
                this->channels.push_back(chan);

                std::cout << client.getNick() << " created channel: " << channel_list[i] << " that doesn't require key" << std::endl;
            }
            Channel &chan1 = this->channels[returnChannelIndex(channel_list[i])];
            chan1.addToOperators(client);
            this->addToChannel(chan1, client);
        }
    }
    channel_list.clear();
    key_list.clear();
}
