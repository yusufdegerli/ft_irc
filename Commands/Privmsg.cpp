#include "../Server/Server.hpp"

void Server :: PRIVMSG(Client &client)
{
    std::string message = "";
    for (size_t j = 2; j < this->commands.size(); j++)
    {
        message += this->commands[j];
        message += " ";
    }
   if (this->commands.size() == 1)
   {
        client.print("Wrong number of arguments\n");
        return ;
   }
   for (size_t i = 0; i < this->clients.size(); i++)
   {
        if(this->commands[1].compare(this->clients[i].getNick()) == 0)
        {
            clients[i].print(client.getNick() + ": " + message + "\n");
            return ;
        }
        else
        {
            std::cout << "getNick: " << this->clients[i].getNick() << std::endl;
            return ;
        }
   }
   
}