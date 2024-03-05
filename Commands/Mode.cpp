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
    {
        this->invite_only = false;
        client.print("Channel is not invite only\n");
    }
    else if (command == '+')
    {
        this->invite_only = true;
        client.print("Channel is invite only\n");
    }
    else
        client.print(client.getNick() + " :Unknown MODE flag\n");
}

void Channel :: operators(char command, Client &operators, Client &client)
{
    if (command == '-')
    {
        if (this->checkOperators(operators))
        {
            this->Operators.erase(this->Operators.begin() + this->returnOperatorIndex(operators.getNick()));
            client.print(operators.getNick() + " is deleted from operators list of the " + this->getName() + " channel\n");
        }   
    }
    else if (command == '+')
    {
        this->Operators.push_back(operators);
        client.print(operators.getNick() + " is added as an operator in " + this->getName() + " channel\n");
    }
    else
        client.print(client.getNick() + " :Unknown MODE flag\n");
}

void Channel :: keys(char command, std::string key, Client &client)
{
    if (command == '-')
    {
        this->key_required = false;
        this->key = "";
        client.print("Channel doesn't requere a key\n");
    }
    else if (command == '+')
    {
        this->key_required = true;
        this->key = key;
        client.print("Channel requeres a key\n");
    }
    else
        client.print(client.getNick() + " :Unknown MODE flag\n");
}


void Server :: MODE(Client &client)
{
    if (this->checkActivation(client) == -1)
        return;
    
    if (this->commands.size() != 3 && this->commands.size() != 4)
    {
        client.print(client.getNick() + " MODE :Not enough parameters\n");
        return;
    }
    
    if (this->commands[1][0] != '#')
    {
        client.print("Try #channel_name\r\n");
        return;
    }
    if (!this->findChannel(this->commands[1]))
    {
        client.print(client.getNick() + " :No such channel\n");
        return;
    }
    else
    {
        Channel &channel = this->channels[returnChannelIndex(this->commands[1])];
        if (!channel.checkOperators(client))
        {
            client.print(client.getNick() +  " " + channel.getName() + " :You're not channel operator\n");
            return ;
        }
        
        if (this->commands[2][1] == 'i' && this->commands[2].size() == 2)
            channel.inviteOnly(this->commands[2][0], client);
        else if (this->commands[2][1] == 'o' && this->commands[2].size() == 2)
        {
            if (this->getClient(this->commands[3]) == -1)
            {
                client.print(client.getUsername() + ": " + this->commands[3] + " :No such nick/channel\r\n");
                return ;
            }
            channel.operators(this->commands[2][0], this->clients[this->getClient(this->commands[3])], client);
        }
        else if (this->commands[2][1] == 'k' && this->commands[2].size() == 2)
            channel.keys(this->commands[2][0], this->commands[3], client);
        else
            client.print(client.getNick() + " :Unknown MODE flag\n");
    }

}