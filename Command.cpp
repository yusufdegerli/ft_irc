
#include "Server.hpp"
#include "Client.hpp"
#include "Command.hpp"


int Command::commandCntl(std::string commandline, int acc_val)
{
    if (!commandline.find("QUIT"))
        commandQuit(commandline, acc_val);
    return (0);
}

void Command::commandQuit(std::string commandline, int acc_val)
{
    int res = commandline.find("QUIT");
    std::string reason;
    if(res == 0)
    {
        if(commandline.size() == 5)
        {
            std::cout << "QUIT: Client exiting from the network\n";
        }
        else
        {
            reason = commandline.substr(4, commandline.size() - 4);
            std::cout << "QUIT:" << reason << std::endl;
            close(acc_val);
        }
        close(acc_val);
    }

}

void    Command::commandJoin(std::string commandline, int acc_val)
{
    //commandline'da hala JOIN var diyelim.

    (void)acc_val;
    std::string parameters = commandline.substr(5, commandline.size());
    std::string channel = parameters.substr(0, parameters.find(' '));
    std::string keys = parameters.substr(parameters.find(' '), parameters.size());

    std::vector<std::string> channels;
     
}

void Server :: PASS(Client &client)
{
    if (client.getLoggedStatus() == 1)
    {
        client.print("You are already in the system\n");
        return ;
    }
    if (this->commands.size() != 2)
    {
        client.print("Wrong number of arguments\n");
        return ;
    }

    if (this->password == this->commands[1])
        client.setLoggin();
    else
        client.print("Wrong password. Try again\n");
}

void Server :: NICK(Client &client)
{
    if (client.getNick() != "")
    {
        client.print("Nickname is already set\n");
        return ;
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

    client.setUsrNick(this->commands[1]); // check if the same nick exists already
    // client.print("Welcome, " + client.getNick() + "\n");
}
void Server :: USER(Client &client)
{
    if (client.getName() != "")
    {
        client.print("Real name is already set\n");
        return ;
    }
    if (client.getLoggedStatus() == 0)
    {
        client.print("Log into the system first. Use PASS command\n");
        return ;
    }
    
    if (client.getNick() == "")
    {
        client.print("Set nickname first. Use NICK command\n");
        return ;
    }

    if (this->commands.size() != 2)
    {
        client.print("Wrong number of arguments\n");
        return ;
    }

    client.setUsrName(this->commands[1]);
}