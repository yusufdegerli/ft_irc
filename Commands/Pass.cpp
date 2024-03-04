#include "../Server/Server.hpp"

void Server :: PASS(Client &client)
{
    if (client.getLoggedStatus() == true)
    {
        client.print(":" + client.getRealIp() + " 462 " + client.getNick() + " : You are already logged\r\n");
        return ;
    }

    if (this->commands.size() != 2)
    {
        client.print(":" + client.getRealIp() + " 461 " + client.getNick() + "PASS : Wrong number of parameters\r\n");
        return ;
    }

    if (this->password == this->commands[1]) //at first come to the func, it should keep the pass. After that it should check. !you keep the wrong password(server pass)!
    {
        client.setUsrPass(commands[1].substr(1, commands[1].size() -1)); //keep the password
        client.setLoggin();
    }
    else
    {
        // std::cout << this->password << std::endl;
        client.print(":" + client.getRealIp() + " 464 " + client.getNick() + "PASS : Password incorrect\r\n");
    }
}
