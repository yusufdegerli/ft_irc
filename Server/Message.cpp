#include "Server.hpp"

void Server :: parseMessage(char *buffer)
{
    std::string str(buffer);
    if (str.length() == 0)
        return ;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] >= 9 && str[i] <= 13)
            str[i] = ' ';
    }

    std::string comm;
    std::istringstream buff(str);
    this->commands.clear();

    while (std::getline(buff, comm, ' '))
    {
        if (comm.length() > 0)
            this->commands.push_back(comm);
    }

    str.clear();
}

void Server :: executeCommands(int fd)
{
    Client *client = &this->clients[fd - 1];

    void (Server::*cmds[])(Client &client) = {&Server::PASS, &Server::NICK, &Server::USER, &Server::JOIN, &Server::QUIT, &Server::INVITE, &Server::WHO, &Server::PRIVMSG};
    std::string commands[] = {"PASS", "NICK", "USER", "JOIN", "QUIT", "INVITE", "WHO", "PRIVMSG"};
    size_t i;

    if (this->commands.size() == 0)
        return ;
    for (i = 0; i < 8; i++)
    {
        if (this->commands[0] == commands[i]) // check activation for all functions
        {
            (this->*(cmds[i]))(*client);
            break;
        }
    }
    if (i == 8)
    {
        client->print("Command wasn't found\n");
    }
}

int Server :: checkActivation(Client &client)
{
    if (client.getLoggedStatus() == 0)
    {
        client.print("Log into the system first. Use PASS command\n");
        return -1;
    }

    if (client.getNick() == "")
    {
        client.print("Set nickname first. Use NICK command\n");
        return -1;
    }

    if (client.getName() == "")
    {
        client.print("Set real name first. Use USER command\n");
        return -1;
    }
    return 1;
}