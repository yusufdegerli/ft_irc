#include "Server.hpp"

int main(int ac, char **av)
{
    if(ac != 3)
    {
        std::cerr << "Error! You need use 2 arguemnts!\n";
        return EXIT_FAILURE;
    }
    else
    {
        Server serv(atoi(av[1]), av[2]);
    }
    serverFunc();
    return 0;
}