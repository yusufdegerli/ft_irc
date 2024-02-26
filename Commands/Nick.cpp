#include "../Server.hpp"

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

    client.setUsrNick(this->commands[1]); // check if the same nick exists already
}
