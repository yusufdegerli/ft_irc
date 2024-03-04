#include "../Server/Server.hpp"

// Ünlemden sonra (!) host gelicek
void Server :: NICK(Client &client)
{
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
    if (!client.getinServer())
    {
        client.print("Log into the system first. Use PASS command\n");
        return ;
    }

    if (this->commands.size() != 2 || this->commands.size() == 1)
    {
        client.print(":<serverip> or <hostname> 431 " + client.getNick() + " : No nickname given\r\n");
        return ;
    }
    
    for (size_t i = 0; i < this->clients.size(); i++)
    {
        if (this->clients[i].getNick() == this->commands[1] && client.getLoggedStatus() == 0)
        {
            client.print(":<serverip> or <hostname> 433 " + client.getNick() + " " + this->commands[1]\
             + " :Nickname is already in use\r\n");
            return ;
        }
    }
    client.setUsrNick(this->commands[1]);
}
