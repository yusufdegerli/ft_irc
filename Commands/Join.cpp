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
    new_list.push_back(str.substr(start));

    return(new_list);
}

bool Server :: findChannel(std::string channel)
{
    for (size_t i = 0; i < this->channels.size(); i++)
    {
        if (this->channels[i].getName() == channel)
            return true;
    }

    return false;
}

size_t Server :: returnChannelIndex(std::string channel)
{
    size_t i = 0;

    for (; i < this->channels.size(); i++)
    {
        if (this->channels[i].getName() == channel)
            return i;
    }

    return i;
}

void Server :: addToChannel(Channel &chan, Client &client)
{
    if (chan.checkMembers(client) == false)
    {
        client.print("You entered the channel " + chan.getName() + "\n");
        chan.addToMembers(client);
    }
    else
        client.print("You are already in the channel " + chan.getName() + "\n");
}


void Server :: JOIN(Client &client) // usage JOIN <channel>{,<channel>} [<key>{,<key>}]
{
    // std::vector<Channel>  *channel = &this->channels;

    std::string channels = this->commands[1];
    std::string keys = this->commands[2];

    std::cout << client.getNick() << std::endl;
    if (channels.empty())
    {
        client.print(client.getNick() + " JOIN :Not enough parameters" + "\r\n"); // 461
        return ;
    }
    std::vector<std::string> channel_list;
    channel_list = create_list(channels);

    std::vector<std::string> key_list;
    key_list = create_list(keys);

    for (size_t i = 0; i < channel_list.size(); i++)
    {
        if (this->findChannel(channel_list[i]))
        {
            Channel &chan = this->channels[returnChannelIndex(channel_list[i])];
            std::cout << "key requeru " << chan.getKeyRequired() << std::endl;
            if (chan.getKeyRequired())
            {
                std::cout << "check keys " << key_list[i] << " and " << chan.getKey() << std::endl;
                if (key_list[i] == chan.getKey())
                    this->addToChannel(chan, client);
                else
                {
                    client.print("Enter the key to join channel " + chan.getName() + "\n");
                }
            }
            else
                this->addToChannel(chan, client);
        }
        else
        {
            std::cout << "create channel, key list = '" << key_list[i] << "' and i = " << i << std::endl;
            if (key_list[i] != "")
            {
                Channel chan(channel_list[i], key_list[i]);
                this->channels.push_back(chan);

                std::cout << client.getNick() << " created channel: " << channel_list[i] << " that requires key" << std::endl;
                client.print("You created channel: " + channel_list[i] + "\n");

                Channel &chan1 = this->channels[returnChannelIndex(channel_list[i])];
                this->addToChannel(chan1, client);
            }
            else
            {
                Channel chan(channel_list[i]);
                this->channels.push_back(chan);

                std::cout << client.getNick() << " created channel: " << channel_list[i] << " that doesn't requery key" << std::endl;
                client.print("You created channel: " + channel_list[i] + "\n");

                Channel &chan1 = this->channels[returnChannelIndex(channel_list[i])];
                this->addToChannel(chan1, client);
            }
        }
    }

    // for (size_t k = 0; k < channel_list.size(); k++)
    // {
    //     size_t j = 0;
    //     for (j = 0; j < channel->size(); j++)
    //     {
    //         if (channel_list[k] == (*channel)[j].getName())
    //         {
    //             if ((key_list.empty() && (*channel)[j].getKeyRequired()) || ((!key_list.empty()) && key_list[k] != (*channel)[j].getKey())) //kontrol et *key_list.empty()*   yanlış çalışıyor
    //             {
    //                 client.print(client.getNick() + " " + (*channel)[j].getName() + " :Cannot join channel (+k)" + "\r\n"); // kodu 475
    //                 return ;
    //             }
    //             else
    //             {
    //                 size_t i = 0;
    //                 std::cout << (*channel)[j].getMembers().size() << std::endl;
    //                 for (i = 0; i < (*channel)[j].getMembers().size(); i++)
    //                 { 
    //                     if (client.getNick() == (*channel)[j].getMembers()[i].getNick())
    //                         break ;
    //                 }
    //                 if (i == (*channel)[j].getMembers().size())
    //                 {
    //                     std::cout << "....." << (*channel)[j].getMembers().size() << std::endl;
    //                     //The topic is a line shown to all users when they join the channel
    //                     (*channel)[j].addToMembers(client);
    //                     for (size_t m = 0; m < (*channel)[j].getMembers().size();m++)
    //                         (*channel)[j].getMembers()[m].print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " JOIN " + (*channel)[j].getName() + "\r\n");
    //                 }
    //                 break ;
    //             }
    //         }
    //     }
    //     if (j == channel->size())
    //     {
    //         //The topic is a line shown to all users when they join the channel
    //         this->addToChannels(Channel(channel_list[k]));
    //         (*channel)[j].addToMembers(client);
    //         (*channel)[j].addToOperators(client);
    //         for (size_t m = 0; m < (*channel)[j].getMembers().size();m++)
    //             (*channel)[j].getMembers()[m].print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " JOIN " + (*channel)[j].getName() + "\r\n");
    //     }

    // }
    // //check if the client can join the channel
    // //if a client joins to a channel, all the members should know it.
    // //this command also accepts the special argument of ("0", 0x30) instead of any of the usual parameters, which requests that the sending client leave all channels they are currently connected to. The server will process this command as though the client had sent a PART command for each channel they are a member of.
       
    channel_list.clear();
    key_list.clear();
}
