#include "../Server/Server.hpp"

void Server :: PRIVMSG(Client &client)
{
    size_t i = 0;
    if(this->checkActivation(client) == -1)
        return ;
    std::string message = "";
    if (this->commands.size() > 2)
        message += this->commands[2].substr(1);
    for (size_t j = 3; j < this->commands.size(); j++)
    {
        message += " ";
        message += this->commands[j];
    }
    if (this->commands.size() == 1)
    {
        client.print(":" + this->getServerIP() + " 411 " + client.getNick() + ": No recipient given PRIVMSG\r\n");
        return ;
    }
    else if(this->commands.size() == 2)
    {
        client.print(":" + this->getServerIP() + " 412 " + client.getNick() + ": No recipient given PRIVMSG\r\n");
        return ;
    }
    for (; i < this->clients.size(); i++)
    {
        if(this->commands[1].compare(this->clients[i].getNick()) == 0)
        {
            clients[i].print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " PRIVMSG " + clients[i].getNick() + " :" + message + "\r\n");
            client.print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " PRIVMSG " + clients[i].getNick() + " :" + message + "\r\n");
            return ;
        }
        else if (this->commands[1].compare(this->channels[i].getName()) == 0)
        {
            for (size_t m = 0; m < this->channels[i].getMembers().size(); m++)
                this->channels[i].getMembers()[m].print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " PRIVMSG " + this->channels[i].getName() + " :"+ message + "\r\n");
            return ;
        }
    }
    if(i == clients.size())
    {
        client.print(":" + this->getServerIP() + " 401 " + client.getNick() + ": No such nick/channel\r\n");
        return ;
    }
}