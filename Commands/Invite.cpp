#include "../Server/Server.hpp"

void Server :: INVITE(Client &client)
{
    std::string nickname = this->commands[1];
    std::string channel = this->commands[2];

    if (channels.empty() || nickname.empty())
    {
        client.print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " " + client.getNick() + " INVITE :Not enough parameters" + "\r\n"); // 461
        return ;
    }

    size_t j;
    for (j = 0; j < this->channels.size(); j++)
    {
        if (channel == this->channels[j].getName())
            break ;
    }
    if (j == this->channels.size())
    {
        client.print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " " + client.getNick() + " " + channel + " :No such channel\r\n"); //403
        return ;
    }
    size_t i;
    for (i = 0; i < (this->channels[j].getMembers()).size(); i++)
    {
        if (client.getNick() == (this->channels[j].getMembers())[i].getNick())
            break ;
        if (nickname == (this->channels[j].getMembers())[i].getNick())
        {
            client.print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " " + client.getNick() + " " + nickname + " " + channel + " :is already on channel\r\n"); //443
            return ;
        }
    }
    if (i == this->channels[j].getMembers().size())
    {
        client.print(client.getNick() + " " + channel + " :You're not on that channel\r\n"); //442
        return ;
    }
    size_t k;
    for (k = 0; k < this->channels[j].getOperators().size(); k++)
    {
        if (client.getNick() == (this->channels[j].getOperators())[k].getNick())
            break ;
    }
    if (this->channels[j].getInviteOnly() && k == this->channels[j].getOperators().size())
    {
        client.print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " " + client.getNick() + " " + channel + " :You're not channel operator\r\n"); //482
        return ;
    }
    client.print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " " + client.getNick() + " " + nickname + " " + channel + "\r\n"); //341
    for (size_t m = 0; m < this->clients.size(); m++)
    {
        if (this->clients[m].getNick() == nickname)
        {
            this->clients[m].print(":" + this->clients[m].getNick() + "!" + this->clients[m].getUsername() + '@' + this->clients[m].getRealIp() + " " + client.getNick() + " " + nickname + " " + channel + "\r\n");
            break ;
        }
    }
    //message to client
}