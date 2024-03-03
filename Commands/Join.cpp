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

void Server :: JOIN(Client &client) // usage JOIN <channel>{,<channel>} [<key>{,<key>}]
{
    std::string channels = this->commands[1];
    std::vector<std::string> key_list;
    std::string keys;
    if (this->commands.size() != 3)
    {
        keys = "";
        key_list.push_back("");
    }
    else
    {
        keys = this->commands[2];
        key_list = create_list(keys);
    }

    if (this->commands.size() != 2)
    {
        client.print(":" + client.getRealIp() + " 461 " + client.getNick() + "JOIN : Not enough parameters\n");
        return ;
    }
    std::vector<std::string> channel_list;
    channel_list = create_list(channels);

    for (size_t i = 0; i < channel_list.size(); i++)
    {
        if(channel_list[i][0] != '#')
        {
            client.print("JOIN: There is no # in the first character.\n");
            return ;
        }
        if (this->findChannel(channel_list[i])) //channel var
        {
            Channel &chan = this->channels[returnChannelIndex(channel_list[i])];
            std::cout << "key requeru " << chan.getKeyRequired() << std::endl;
            if (chan.getKeyRequired() && !keys.empty())
            {
                std::cout << "check keys " << key_list[i] << " and " << chan.getKey() << std::endl;
                if (key_list[i] == chan.getKey())
                    this->addToChannel(chan, client);
                else
                {
                    client.print(client.getNick() + " " + chan.getName() + " :Cannot join channel (+k)" + "\r\n"); // kodu 475
                }
            }
            else
                this->addToChannel(chan, client);
        }
        else //yok
        {
            //std::cout << "create channel, key list = '" << key_list[i] << "' and i = " << i << std::endl;
            if (key_list[i] != "")
            {
                Channel chan(channel_list[i], key_list[i]);
                this->channels.push_back(chan);

                std::cout << client.getNick() << " created channel: " << channel_list[i] << " that requires key" << std::endl;
                client.print("You created channel: " + channel_list[i] + "\n");

                Channel &chan1 = this->channels[returnChannelIndex(channel_list[i])];
                chan1.addToOperators(client);
                this->addToChannel(chan1, client);
            }
            else
            {
                Channel chan(channel_list[i]);
                this->channels.push_back(chan);

                std::cout << client.getNick() << " created channel: " << channel_list[i] << " that doesn't requery key" << std::endl;
                client.print("You created channel: " + channel_list[i] + "\n");

                Channel &chan1 = this->channels[returnChannelIndex(channel_list[i])];
                chan1.addToOperators(client);
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
