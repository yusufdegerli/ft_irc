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
            // if(!client.getUsername(this.commands[1]).empty())
            client.print("@");
            client.print(client.getRealIp());
            client.print("\n");
        }
        // client.print("Nickname is already set\n");
            // std::cout << "oldName: " << oldName << " nameCnt: " << nameCnt << std::endl;
        nameCnt++;
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
