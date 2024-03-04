#include "../Server/Server.hpp"

void Server :: PASS(Client &client)
{
    if (client.getLoggedStatus())
    {
        client.print(":<serverip> or <hostname> 462 " + client.getNick() + " : You are already logged\r\n");
        return ;
    }

    if (this->commands.size() < 2)
    {
        client.print(":<serverip> or <hostname> 461 " + client.getNick() + "PASS : Not enough parameters\r\n");
        return ;
    }

    if (this->password == this->commands[1].substr(1))
    {
        client.print("You are in the system\n");
        client.setInServer(true);
    }
    else
    {
        //std::cout << this->password << std::endl;
        client.print(":<serverip> or <hostname> 464 " + client.getNick() + "PASS : Password incorrect\r\n");
    }
}
