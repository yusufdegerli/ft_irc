#include "../Server/Server.hpp"

void Server::QUIT(Client &client)
{
    std::string reason;
    (void)client;
    if(this->commands[0].size() == 5)
    {
        std::cout << "QUIT: Client exiting from the network\r\n";
        close(this->acc_val);
    }
    else
    {
        for (size_t i = 0; i < this->commands.size(); i++)
            reason += this->commands[i];
        std::cout << "QUIT:" << reason << std::endl;
        close(this->acc_val);
    }
    close(this->acc_val);

}