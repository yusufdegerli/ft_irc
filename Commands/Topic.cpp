#include "../Server/Server.hpp"

void Server::TOPIC(Client &client)
{
    std::string topic = "";

    if (this->commands.size() < 2)
    {
        client.print("::" + this->getServerIP() + " 461 "+ client.getNick() + " TOPIC :Not enough parameters" + "\r\n");
        return ;
    }
    if (this->commands.size() == 3)
        topic = this->commands[1].substr(1);
    if (this->findChannel(this->commands[1]))
    {
        Channel &chan = this->channels[returnChannelIndex(this->commands[1])];
        for (size_t j = 3; j < this->commands.size(); j++)
            topic += " " + this->commands[j];
        if (topic[0] == ':')
        {
            if (!topic.compare(":"))
                chan.setTopic("");
            else
                chan.setTopic(topic);
        }
        else
            client.print(":" + this->getServerIP() + " 332 " + client.getNick() + " "+ chan.getName() + ":" + chan.getTopic() + "\r\n");//332
    }
    else
    {
        client.print(":" + this->getServerIP() + " 403 " + client.getNick() + " " + this->commands[1] + " :No such channel\r\n");
        return ;
    }
}