#include "../Server/Server.hpp"

void Server :: JOIN(Client &client)
{
    std::vector<Channel>  *channel = &this->channels;

    std::string channels = this->commands[1];
    std::string keys = this->commands[2];

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

    for (size_t k = 0; k < channel_list.size(); k++)
    {
        size_t j;
        for (j = 0; j < channel->size(); j++)
        {
            if (channel_list[k] == (*channel)[j].getName())
            {
                //*check if the client is already in the channel.*
                (*channel)[j].addToMembers(client);
                std::cout << (*channel)[j].getName() << std::endl;
                break;
            }
        }
        if (j == channel->size())
        {
            this->addToChannels(Channel(channel_list[k]));
            (*channel)[j].addToMembers(client);
            std::cout << "aaaaaa: " << this->channels[j].getName() << std::endl;
        }
    }

    std::vector<std::string> key_list;
    index = keys.find(',');
    start = 0;
    while (index != std::string::npos)
    {
        key_list.push_back(keys.substr(start, index - start));
        start = index + 1;
        index = keys.find(',', start);
    }
    key_list.push_back(keys.substr(start));


    //check if the client can join the channel
    //if a client joins to a channel, all the members should know it.
    //this command also accepts the special argument of ("0", 0x30) instead of any of the usual parameters, which requests that the sending client leave all channels they are currently connected to. The server will process this command as though the client had sent a PART command for each channel they are a member of.

    channel_list.clear();
    key_list.clear();
}