#include "../Server/Server.hpp"

void Server :: USER(Client &client)
{
    if (client.getName() != "")
    {
        client.print("Real name is already set\n");
        return ;
    }
    if (client.getLoggedStatus() == 0)
    {
        client.print("Log into the system first. Use PASS command\n");
        return ;
    }
    
    if (client.getNick() == "")
    {
        client.print("Set nickname first. Use NICK command\n");
        return ;
    }

    if (this->commands.size() != 2)
    {
        client.print("Wrong number of arguments\n");
        return ;
    }

    client.setUsrName(this->commands[1]);

    // client.setUsername(this->commands[1]);
    // client.setHostname(this->commands[3]); // nothing is passed as 4th str
}