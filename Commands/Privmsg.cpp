#include "../Server/Server.hpp"

void Server :: PRIVMSG(Client &client)
{
   if (this->commands.size() != 3)
   {
        client.print("Wrong number of arguments\n");
        return ;
   }
   for (size_t i = 0; i < this->clients.size(); i++)
   {
    if(this->commands[1].compare(this->clients[i].getNick()) == 0)
    {
        this->clients[i].print("                : ");
        this->clients[i].print(commands[2]);
        this->clients[i].print("\n");
        return ;
    }
    else
    {
        std::cout << "getNick: " << this->clients[i].getNick() << std::endl;
        return ;
    }
   }
   
    // std::cout << "getNick: " << client.getNick() << std::endl;
}