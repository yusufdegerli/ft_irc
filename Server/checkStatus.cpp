#include "Server.hpp"

void Server :: checkPollStatus(int poll_status)
{
    if (poll_status == -1) 
    {
        perror("Poll error");
        exit(EXIT_FAILURE);
    }
}

void Server :: checkBindStatus(int bind_val)
{
    if (bind_val == -1)
    {
        std::cerr << "bind error" << std::endl;
        exit(1);
    }
}

void Server :: checkListenStatus(int list_val)
{
    if (list_val == -1)
    {
        std::cerr << "listen error" << std::endl;
        exit(1);
    }
}

void Server :: checkAcceptStatus(int accept_val)
{
    if (accept_val == -1)
    {
        std::cerr << "accept error" << std::endl;
        exit(1);
    }

    this->acc_val = accept_val;
}

int Server :: checkRecvStatus(int recv_val, int i)
{
    if (recv_val < 0)
    {
        std::cerr << "Recv error" << std::endl;
        exit(1);
    }
    else if (recv_val == 0)
    {
        this->commands.clear();
        this->commands.push_back("QUIT");
        this->QUIT(this->clients[this->acc_val - 4]);
        std::cout << "Client " << i + 3 << " logged out" << std::endl;
        close(this->fds[i].fd);
        this->fds[i].fd = 0;
        return 0;
    }
    return 1;
}