#pragma once
#include <iostream>
#include <map>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

class CommandsBot{
	private:
		int											_socket;
		std::string									nickName;
		std::string									userName;
		std::map<std::string,void(CommandsBot::*)()>	funcMap;
		std::map<std::string,std::string>			comMap;
		std::vector<std::string>					splitted;
		std::vector<std::string>					parsed;
		std::string 								parseSenderName();
		std::string									createClientMsg();
	public:
		CommandsBot(std::string userName, std::string nickName);
		~CommandsBot();
		void	runComs(std::string coms);

		//COMMANDS
		void	cmdHelp();
		void	cmdCmd();

		//SET FUNCS
		void	setSocket(int socket);

		//GET FUNCS
		int	getSocket() const;
};
