#include "../Server/Server.hpp"

void Server :: LIST(Client &client)
{
    std::string list;
    for(size_t i = 0; i < this->channels.size(); i++)
    {
        list += this->channels[i].getName() + " " + this->channels[i].getTopic();
    }
    client.print(":" + client.getRealIp() + list + "\r\n");
}