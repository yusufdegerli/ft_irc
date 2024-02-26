
#include "Server.hpp"
#include "Client.hpp"

void Server :: PASS(Client &client)
{
    if (client.getLoggedStatus() == 1)
    {
        client.print("You are already in the system\n");
        return ;
    }
    if (this->commands.size() != 2)
    {
        client.print("Wrong number of arguments\n");
        return ;
    }

    if (this->password == this->commands[1])
        client.setLoggin();
    else
        client.print("Wrong password. Try again\n");
}

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
    // client.print("Welcome, " + client.getNick() + "\n");
}
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
}