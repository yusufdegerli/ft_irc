#include "Bot.hpp"



Bot::Bot(int port, std::string password) : CommandsBot("bot", "bot"){
	userName = "bot";
	nickName = "bot";
	_socket = socket(AF_INET, SOCK_STREAM, 0);
    CommandsBot::setSocket(_socket);
	if (_socket == -1) {
		std::cerr << "Socket creation failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port); // Server port
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address
	if (connect(_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		std::cerr << "Connection failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string msg = "PASS :" + password + "\r\nUSER " + userName + " 0 127.0.0.1 :Official irc bot\r\nNICK " + nickName + "\r\n";
	ssize_t bytesSent = send(_socket, msg.c_str(), msg.length(), 0);
	if (bytesSent == -1) {
		std::cerr << "Send failed" << std::endl;
	} else {
		std::cout << "Sent " << bytesSent << " bytes: " << msg << std::endl;
	}
}

Bot::~Bot(){
	close(_socket);
}

//SET FUNCS
void	Bot::setSocket(int socket){	this->_socket = socket; }

//GET FUNCS
int	Bot::getSocket() const { return (_socket); }

const char *Bot::PortMaxException::what(void) const throw()
{
	return ("Error: Port max number is 65535");
};

const char *Bot::PortMinException::what(void) const throw()
{
	return ("Error: Port min number is 0");
};