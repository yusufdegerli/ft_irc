#include <iostream>

bool ft_pass(std::string password, bool logged)
{
    std::string str;

    if (logged == true)
    {
        std::cout << "You are already logged" << std::endl;
        return true;
    }
    std::cout << "Enter password" <<std::endl; 
    std::getline(std::cin, str); 

    if (!str.compare(password))
        std::cout << "You are logged" << std::endl;
    else
    {
        std::cout << "Wrong password. Try again." << std::endl;
        ft_pass(password, logged);
    }
    return true;
}

std::string ft_nick(bool logged)
{
    if (logged == false)
    {
        std::cout << "Log in first" << std::endl;
        return "";
    }

    std::string str = "";
    std::cout << "Enter nickname" <<std::endl;
    while (str == "")
        std::getline(std::cin, str); //then check if the same name already exists
    std::cout << "Your nickname is " << str <<std::endl;
    return str;

}

std::string ft_name(bool logged, std::string nick)
{
    if (logged == false || nick == "")
    {
        std::cout << "Log in first and set nick name first" << std::endl;
        return "";
    }

    std::string str;
    std::cout << "Enter name" <<std::endl;
    while (str == "")
        std::getline(std::cin, str); //then check if the same name already exists
    std::cout << "Your name is " << str <<std::endl;
    return str;

}


int main(int argc, char **argv)
{
    (void)argv;
    if (argc != 3)
    {
        std::cout << "Usage: ./irserv <port> <password>" << std::endl;
        return 1;
    }
    std::string str;
    while(1)
    {
        std::cout << "Enter port number to connect as user" <<std::endl; 
        std::getline(std::cin, str);
        if (!str.compare(argv[1]))
        {
            std::cout << "SERVER: Client connected" << std::endl;
            break;
        }
        else
            std::cout << "SERVER: Wrong port" << std::endl;
    }
    bool logged = false;
    std::string nickname;
    std::string name;
    while(1)
    {   
        std::string commands[] = {"PASS", "NICK", "USER"};

        std::cout << "Enter command: " << std::endl;

        std::getline(std::cin, str);
        size_t i;
        for (i = 0; i < commands->size(); i++)
        {
            if (!str.compare(commands[i]))
                break;
        }
        switch (i)
        {
            case 0:
                logged = ft_pass(argv[2], logged);
                break;
            case 1:
                nickname = ft_nick(logged);
                break;
            case 2:
                name = ft_name(logged, nickname);
                break;
            default:
                std::cout << "Command not found" << std::endl;
                break;
        }
    }
}

void Server::createServer()
{
	this->setServerFd(socket(AF_INET, SOCK_STREAM, 0));
	fcntl(this->serverFd, F_SETFL, O_NONBLOCK);	
	setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &(this->opt), sizeof(opt));

	bind(this->serverFd, reinterpret_cast<const struct sockaddr *>(&(this->address)), sizeof(struct sockaddr_in));
	listen(this->serverFd, 3);
	memset(this->getFds(), 0, 100);
	this->fds[0].fd = this->serverFd;
	this->fds[0].events = POLLIN;
}

void Server::start()
{
	std::cout << "Server started" << std::endl;
	while (1)
	{
		poll(this->fds, 10, -1);
		userAccept();
		for(int fd = 4; fd < 10; fd++)
		{
			if (this->getFds()[fd].revents & POLLIN)
			{
				readMessage(fd);
				parseMessage();
				controlMessage(fd);
			}
		}
	}
}