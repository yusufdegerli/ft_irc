#include "../Server/Server.hpp"

int Server :: getClient(std::string nick)
{
    for (size_t i = 0; i < this->clients.size(); i++)
    {
        if (this->clients[i].getNick() == nick)
            return i;
    }

    return -1;
}

int Channel :: returnOperatorIndex(std::string nick)
{
    for (size_t i = 0; i < this->Operators.size(); i++)
    {
        if (this->Operators[i].getNick() == nick)
            return i;
    }
    return -1;
}


void Channel :: inviteOnly(char command, Client &client)
{
    if (command == '-')
        this->invite_only = false;
    else if (command == '+')
        this->invite_only = true;
    else
        client.print("Wrong use of the invite only mode command. Try +- before the keyword\n");
}

void Channel :: operators(char command, Client &operators, Client &client)
{
    if (command == '-')
    {
        std::cout << "size before remove: " << this->Operators.size() << std::endl;
        if (this->checkOperators(operators))
        {
            client.print("hopefully deleted\n");
            this->Operators.erase(this->Operators.begin() + this->returnOperatorIndex(operators.getNick()));        
        }   
        std::cout << "size after remove: " << this->Operators.size() << std::endl;
    }
    else if (command == '+')
    {
        std::cout << "size before add: " << this->Operators.size() << std::endl;
        this->Operators.push_back(operators);
        std::cout << "size after add: " << this->Operators.size() << std::endl;
    }
    else
        client.print("Wrong use of the operators mode command. Try +- before the keyword\n");
}

void Channel :: keys(char command, std::string key, Client &client)
{
    if (command == '-')
    {
        this->key_required = false;
        this->key = "";
    }
    else if (command == '+')
    {
        this->key_required = true;
        this->key = key;
    }
    else
        client.print("Wrong use of the key mode command. Try +- before the keyword\n");
}


void Server :: MODE(Client &client)
{
    if (this->checkActivation(client) == -1)
        return;
    
    if (this->commands.size() != 3 && this->commands.size() != 4)
    {
        client.print("Not enough arguments\n");
        return;
    }
    
    if (this->commands[1][0] != '#')
    {
        client.print("Try #channel_name\n");
        return;
    }
    if (!this->findChannel(this->commands[1]))
    {
        client.print("Channel doesn't exist\n");
        return;
    }
    else
    {
        Channel &channel = this->channels[returnChannelIndex(this->commands[1])];
        if (!channel.checkOperators(client))
        {
            client.print("Only operators of the channel can use MODE command and you are not one\n");
            return ;
        }
        
        if (this->commands[2][1] == 'i' && this->commands[2].size() == 2)
            channel.inviteOnly(this->commands[2][0], client);
        else if (this->commands[2][1] == 'o' && this->commands[2].size() == 2)
        {
            if (this->getClient(this->commands[3]) == -1)
            {
                client.print("Client with this nick doesn't exist\n");
                return ;
            }
            channel.operators(this->commands[2][0], this->clients[this->getClient(this->commands[3])], client);
        }
        else if (this->commands[2][1] == 'k' && this->commands[2].size() == 2)
            channel.keys(this->commands[2][0], this->commands[3], client);
        else
            client.print("The kws of the command was not found\n");
    }

}