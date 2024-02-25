#include "Server.hpp"

int main(int ac, char **av)
{
    if(ac != 3)
    {
        std::cerr << "Usage: ./irserv <port> <password>" << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        Server serv(atoi(av[1]), av[2]);
        serv.serverFunc();
    }
    return 0;
}