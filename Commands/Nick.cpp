#include "../Server/Server.hpp"

void Server :: NICK(Client &client)
{
    if(client.getinServer() == false)
    {
        client.print("Log into the system first. Use PASS command\n");
        return ;
    }
    else if(this->commands.size() > 2)
    {
        client.print("There's have to be only one argument for the nickname\n");
        return ;
    }
     if (client.getNick() != "")
    {
        std::string oldName = "";
        static int nameCnt = 0;
            oldName = client.getNick();
        if(nameCnt >= 0)
        {
            client.print(":");
            if(!oldName.empty())
                client.print(oldName);
            client.print("!");
            client.print("@");
            client.print(client.getRealIp());
            client.print("\n");
        }
        nameCnt++;
    }

    if (this->commands.size() == 1)
    {
        client.print(":" + this->getServerIP() + " 431 " + client.getNick() + " :No nickname given\r\n");
        return ;
    }
    for (size_t i = 0; i < this->clients.size(); i++)
    {
        if (this->clients[i].getNick() == this->commands[1] && client.getLoggedStatus() == 0)
        {
            client.print(":" + this->getServerIP() + " 433 " + client.getNick() + " " + this->commands[1]\
             + " :Nickname is already in use\r\n");
            return ;
        }
    }
    client.setUsrNick(this->commands[1]);
}
