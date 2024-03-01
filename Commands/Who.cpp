#include "../Server/Server.hpp"

void Server :: WHO(Client &client)
{
    // (void)client;
    size_t i = 0;
    // std::cout << "commands[1]: " << this->commands[1] << std::endl;
    // std::cout << "this->channels[0].getName(): " << this->channels[0].getName() << std::endl;
    // std::cout << "this->chnnels[0].getMembers()[0].getName(): "<< this->channels[0].getMembers()[0].getName()<<std::endl;
    for (; i < this->channels.size(); i++)
    {
        std :: cout << this->channels[i].getName() << std :: endl;
        if(this->commands[1].compare(this->channels[i].getMembers()[i].getNick()) == 0)
        {
            // std::cout << this->channels[i].getMembers()[i].getName() << std::endl;
            for (size_t m = 0; m < this->channels[i].getMembers().size(); m++)
            {
                // std::cout << this->channels[i].getMembers()[m].getNick()<< std::endl;
                client.print("Nick: " + this->channels[i].getMembers()[i].getNick() + "\n");
                client.print("Ip: " + this->channels[i].getMembers()[i].getRealIp() + "\n");
                client.print("Hostname: " + this->channels[i].getMembers()[i].getHostname() + "\n");
                client.print("Username: " + this->channels[i].getMembers()[i].getUsername() + "\n");
                client.print("Name: " + this->channels[i].getMembers()[i].getName() + "\n");

            }
            //this->channels[i].writeMembersByName();
            break ;
        }
    }
    if(i >= this->channels.size())
        {
            client.print("Kanal bulunamadı\n");
        }
    std::cout << "Who komutunun içi\n";
}
//for ile if'in yeri değişecek gibi duruyor