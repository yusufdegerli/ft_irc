#include "../Server/Server.hpp"

void Server :: JOIN(Client &client) // usage JOIN <channel>{,<channel>} [<key>{,<key>}]
{
    std::vector<Channel>  *channel = &this->channels;

    std::string channels = this->commands[1];
    std::string keys = this->commands[2];

    std::cout << client.getNick() << std::endl;
    if (channels.empty())
    {
        client.print(client.getNick() + " JOIN :Not enough parameters" + "\r\n"); // 461
        return ;
    }
    std::vector<std::string> channel_list;
    size_t index = channels.find(',');
    size_t start = 0;
    while (index != std::string::npos)
    {
        channel_list.push_back(channels.substr(start, index - start));
        start = index + 1;
        index = channels.find(',', start);
    }
    channel_list.push_back(channels.substr(start));

    std::vector<std::string> key_list;
    index = keys.find(',');
    start = 0;
    while (index != std::string::npos)
    {
        key_list.push_back(keys.substr(start, index - start));
        start = index + 1;
        index = keys.find(',', start);
    }

    for (size_t k = 0; k < channel_list.size(); k++)
    {
        size_t j = 0;
        for (j = 0; j < channel->size(); j++)
        {
            if (channel_list[k] == (*channel)[j].getName())
            {
                if ((key_list.empty() && (*channel)[j].getKeyRequired()) || ((!key_list.empty()) && key_list[k] != (*channel)[j].getKey())) //kontrol et *key_list.empty()*   yanlış çalışıyor
                {
                    client.print(client.getNick() + " " + (*channel)[j].getName() + " :Cannot join channel (+k)" + "\r\n"); // kodu 475
                    return ;
                }
                else
                {
                    size_t i = 0;
                    std::cout << (*channel)[j].getMembers().size() << std::endl;
                    for (i = 0; i < (*channel)[j].getMembers().size(); i++)
                    { 
                        if (client.getNick() == (*channel)[j].getMembers()[i].getNick())
                            break ;
                    }
                    if (i == (*channel)[j].getMembers().size())
                    {
                        std::cout << "....." << (*channel)[j].getMembers().size() << std::endl;
                        //The topic is a line shown to all users when they join the channel
                        (*channel)[j].addToMembers(client);
                        for (size_t m = 0; m < (*channel)[j].getMembers().size();m++)
                            (*channel)[j].getMembers()[m].print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " JOIN " + (*channel)[j].getName() + "\r\n");
                    }
                    break ;
                }
            }
        }
        if (j == channel->size())
        {
            //The topic is a line shown to all users when they join the channel
            this->addToChannels(Channel(channel_list[k]));
            (*channel)[j].addToMembers(client);
            (*channel)[j].addToOperators(client);
            for (size_t m = 0; m < (*channel)[j].getMembers().size();m++)
                (*channel)[j].getMembers()[m].print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " JOIN " + (*channel)[j].getName() + "\r\n");
        }

    }
    //check if the client can join the channel
    //if a client joins to a channel, all the members should know it.
    //this command also accepts the special argument of ("0", 0x30) instead of any of the usual parameters, which requests that the sending client leave all channels they are currently connected to. The server will process this command as though the client had sent a PART command for each channel they are a member of.
       
    channel_list.clear();
    key_list.clear();
}
