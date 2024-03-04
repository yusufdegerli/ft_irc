#include "Bot.hpp"
#include "CommandsBot.hpp"

int main(int ac, char **av){
	if (ac != 3){
		std::cerr << "Wrong argument!" << std::endl;
		exit(EXIT_FAILURE);
	}
	int port;
	std::string password;
	try
	{
		port = std::stoi(av[1]);
		password  = av[2];
		if (port > PORT_MAX)
		{
			throw Bot::PortMaxException();
		}else if (port < 0){
			throw Bot::PortMinException();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	char buffer[4096];
	Bot bot(port, password);
	while (1){
		ssize_t bytesRead = recv(bot.getSocket(), buffer, sizeof(buffer), 0);
		if (bytesRead <= 0) {
			close(bot.getSocket());
			std::cout << "Connection closed." << std::endl;
			break;
		}
		else {
			buffer[bytesRead] = '\0';
			std::cout << "Received " << ":" << buffer << std::endl;
			std::string s = buffer;
			bot.runComs(s);
		}
	}
}