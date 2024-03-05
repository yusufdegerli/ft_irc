#include "../Server/Server.hpp"

void Server :: INVITE(Client &client)
{
    std::string nickname = this->commands[1];
    std::string channel = this->commands[2];

    if(this->checkActivation(client) == -1)
        return ;

    if (this->commands.size() < 3)
    {
        client.print(":" + this->getServerIP() + " 461" + client.getNick() + " INVITE :Not enough parameters" + "\r\n");
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
        client.print(":" + this->getServerIP() + " 403" + client.getNick() + " " + channel + " :No such channel\r\n");
        return ;
    }
    size_t i;
    for (i = 0; i < (this->channels[j].getMembers()).size(); i++)
    {
        if (client.getNick() == (this->channels[j].getMembers())[i].getNick())
            break ;
        if (nickname == (this->channels[j].getMembers())[i].getNick())
        {
            client.print(":" + this->getServerIP() + " 443" + client.getNick() + " " + nickname + " " + channel + " :is already on channel\r\n");
            return ;
        }
    }
    if (i == this->channels[j].getMembers().size())
    {
        client.print(":" + this->getServerIP() + " 442" + client.getNick() + " " + channel + " :You're not on that channel\r\n");
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
        client.print(":" + this->getServerIP() + " 482" + client.getNick() + " " + channel + " :You're not channel operator\r\n");
        return ;
    }
    client.print(":" + this->getServerIP() + " 341" + client.getNick() + " " + nickname + " " + channel + "\r\n");
    for (size_t m = 0; m < this->clients.size(); m++)
    {
        if (this->clients[m].getNick() == nickname)
        {
            client.clientInfo(this->clients[m], this->clients[m]);
            this->clients[m].print(client.getNick() + " " + nickname + " " + channel + "\r\n");
            this->clients[m].setHasInvitationTo(channel);
            break ;
        }
    }

}