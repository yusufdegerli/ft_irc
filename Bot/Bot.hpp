#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "CommandsBot.hpp"
#include "../Client/Client.hpp"

#define PORT_MAX 65535

class Bot: public CommandsBot{
	private:
		int			_socket;
		std::string	userName;
		std::string	nickName;
		sockaddr_in	serverAddr;
	public:
		Bot(int port, std::string password);
		~Bot();
		class PortMaxException : public std::exception
		{
		public:
			virtual const char *what() const throw();
		};
		class PortMinException : public std::exception
		{
		public:
			virtual const char *what() const throw();
		};
		//SET FUNCS
		void	setSocket(int socket);

		//GET FUNCS
		int	getSocket() const;
};
