
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