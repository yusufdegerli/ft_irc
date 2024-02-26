#include "../Server/Server.hpp"

void Server :: NICK(Client &client)
{
    if (client.getNick() != "")
    {
        client.print("Nickname is already set\n");
        return ;
    }

    if (client.getLoggedStatus() == 0)
    {
        client.print("Log into the system first. Use PASS command\n");
        return ;
    }
        
    if (this->commands.size() != 2)
    {
        client.print("Wrong number of arguments\n");
        return ;
    }
    
    for (size_t i = 0; i < this->clients.size(); i++)
    {
        if (this->clients[i].getNick() == this->commands[1])
        {
            client.print("This username already exist\n");
            return ;
        }
    }
    client.setUsrNick(this->commands[1]);
}
