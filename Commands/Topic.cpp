#include "../Server/Server.hpp"

void Server::TOPIC(Client &client)
{
    std::string topic = "";

    if (this->commands.size() != 2)
    {
        client.print(client.getNick() + " TOPIC :Not enough parameters" + "\r\n"); // 461
        return ;
    }
    if (this->findChannel(this->commands[1]))
    {
        Channel &chan = this->channels[returnChannelIndex(this->commands[1])];

    }
    for (size_t j = 2; j < this->commands.size(); j++)
        topic += this->commands[j];
    //if (!topic.compare(":"))
        //this->findChannel(c);
}