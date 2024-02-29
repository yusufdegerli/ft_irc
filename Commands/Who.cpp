#include "../Server/Server.hpp"

void Server :: WHO(Client &client)
{
    size_t i = 0;
    for (; i < this->channels.size(); i++)
    {
        if(!this->commands[1].compare(this->channels[i].getName()))
        {
            //????????????????
                std::cout << this->channels[i].getMembers()[0].getName() << std::endl;
            for (size_t m = 0; m < this->channels[i].getMembers().size(); m++)
                std::cout << this->channels[i].getMembers()[m].getName() << std::endl;
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