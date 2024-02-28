#include "../Server/Server.hpp"

void Server :: INVITE(Client &client)
{
    std::vector<Channel>  *channels = &this->channels;

    std::string nickname = this->commands[1];
    std::string channel = this->commands[2];

    size_t j;
    for (j = 0; j < channels->size(); j++)
    {
        if (channel == (*channels)[j].getName())
            break ;
    }
    if (j == channels->size())
    {
        client.print(client.getNick() + " " + channel + " :No such channel\r\n"); //403
        return ;
    }
    size_t i;
    for (i = 0; i < ((*channels)[j].getMembers()).size(); i++)
    {
        if (client.getNick() == ((*channels)[j].getMembers())[i].getNick())
            break ;
        if (nickname == ((*channels)[j].getMembers())[i].getNick())
        {
            client.print(client.getNick() + " " + nickname + " " + channel + " :is already on channel\r\n"); //443
            return ;
        }
    }
    if (i == (*channels)[j].getMembers().size())
    {
        client.print(client.getNick() + " " + channel + " :You're not on that channel\r\n"); //442
        return ;
    }
    size_t k;
    for (k = 0; k < (*channels)[j].getOperators().size(); k++)
    {
        if (client.getNick() == ((*channels)[j].getOperators())[k].getNick())
            break ;
    }
    if ((*channels)[j].getInviteOnly() && k == (*channels)[j].getOperators().size())
    {
        client.print(client.getNick() + " " + channel + " :You're not channel operator\r\n"); //482
        return ;
    }
    client.print(client.getNick() + " " + nickname + " " + channel);
    //message to client
}