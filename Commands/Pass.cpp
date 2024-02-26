#include "../Server/Server.hpp"

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
