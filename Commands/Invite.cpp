#include "../Server/Server.hpp"

void Server :: INVITE(Client &client)
{
    std::string nickname = this->commands[1];
    std::string channel = this->commands[2];

    if (this->commands.size() < 3)
    {
        client.print(":<serverip> or <hostname> 461" + client.getNick() + " INVITE :Not enough parameters" + "\r\n");
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
        client.print(":<serverip> or <hostname> 403" + client.getNick() + " " + channel + " :No such channel\r\n");
        return ;
    }
    size_t i;
    for (i = 0; i < (this->channels[j].getMembers()).size(); i++)
    {
        if (client.getNick() == (this->channels[j].getMembers())[i].getNick())
            break ;
        if (nickname == (this->channels[j].getMembers())[i].getNick())
        {
            client.print(":<serverip> or <hostname> 443" + client.getNick() + " " + nickname + " " + channel + " :is already on channel\r\n");
            return ;
        }
    }
    if (i == this->channels[j].getMembers().size())
    {
        client.print(":<serverip> or <hostname> 442" + client.getNick() + " " + channel + " :You're not on that channel\r\n");
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
        client.print(":<serverip> or <hostname> 482" + client.getNick() + " " + channel + " :You're not channel operator\r\n");
        return ;
    }
    client.print(":<serverip> or <hostname> 341" + client.getNick() + " " + nickname + " " + channel + "\r\n");
    for (size_t m = 0; m < this->clients.size(); m++)
    {
        if (this->clients[m].getNick() == nickname)
        {
            client.clientInfo(this->clients[m], this->clients[m]);
            this->clients[m].print(client.getNick() + " " + nickname + " " + channel + "\r\n");
            this->clients[m].getHasInvitationTo().push_back(channel);
            break ;
        }
    }

}